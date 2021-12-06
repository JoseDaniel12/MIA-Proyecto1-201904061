//
// Created by jose on 24/08/21.
//

#include <iostream>
#include <math.h>
#include <cstring>

#include "Mkfs.h"
#include "../structs.h"

using namespace std;

Mkfs::Mkfs(const vector<Param> &parametros):Command(parametros) {
    commandName = "MKFS";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-ID") {
            id = quitarComillas(p.value);
        } else if (p.name == "-TYPE") {
            type = p.value;
        } else if (p.name == "-FS") {
            fs = p.value;
        }
    }
}


void Mkfs::run() {
    if (!runnable) {
        return;
    }

    // ________________________________ Obtencion Particion Montada ________________________________

    MountedPartition* mountedPartition;
    for (auto & mp : mountedPartitions) {
        if (mp.id == id) {
            if (mp.partition.part_type == 'P' || mp.partition.part_type == 'L') {
                mountedPartition = &mp;
            } else {
                cout << "Error: Solo se puede montar un sistema de archivos en una partición primaria o lógica." << endl;
                return;
            }
        }
    }

    // Se verifica que se haya encontrado una paritcion montada para establecerle el sistema de archivos
    if (mountedPartition == nullptr) {
        cout << "Error: No se encontro particion montada con ese id." << endl;
        return;
    }

    // ________________________________ Creacion Elementos Sistema Archivos ________________________________

    // Creacion del super Bloque
    SuperBloque superBloque;
    superBloque.s_filesystem_type = (fs == "EXT3")? 3 : 2;
    int n = getNumberInodos(mountedPartition->partition.part_size, superBloque.s_filesystem_type);
    superBloque.s_inodes_count = n;
    superBloque.s_blocks_count = 3 * n;
    superBloque.s_free_blocks_count = superBloque.s_blocks_count - 2;
    superBloque.s_free_inodes_count = superBloque.s_inodes_count - 2;
    superBloque.s_mtime = time(nullptr);
    superBloque.s_mnt_count = 1;
    superBloque.s_magic = 61267;
    superBloque.s_inode_size = sizeof(Inodo);
    superBloque.s_block_size = 64;
    superBloque.s_first_ino = 2;
    superBloque.s_first_blo = 2;
    // Inicio del bitmap de inodos
    if (superBloque.s_filesystem_type == 2) {
        superBloque.s_bm_inode_start = mountedPartition->partition.part_start + sizeof(SuperBloque);
    } else if (superBloque.s_filesystem_type == 3) {
        superBloque.s_bm_inode_start = mountedPartition->partition.part_start + sizeof(SuperBloque) + (100 * 64);
    } else {
        superBloque.s_bm_inode_start = -1;
    }
    superBloque.s_bm_block_start = superBloque.s_bm_inode_start + n;
    superBloque.s_inode_start = superBloque.s_bm_block_start + 3 * n;
    superBloque.s_block_start = superBloque.s_inode_start + n * sizeof(Inodo);

    // Creacion del Bitmap de Inodos
    char bitmapInodos[n];
    bitmapInodos[0] = bitmapInodos[1] = '1';
    for (int i = 2; i < n; i++) {
        bitmapInodos[i] = '0';
    }

    // Creacion del Bitmap de Bloques
    char bitmapBloques[3 * n];
    bitmapBloques[0] = bitmapBloques[1] = '1';
    for (int i = 2; i < 3 * n; i++) {
        bitmapBloques[i] = '0';
    }

    // Creacion del Journaling
    Journaling journaling;


    // ________________________________ Escritura Elementos Sistema Archivos ________________________________

    FILE* file =  fopen(mountedPartition->path.c_str(), "rb+");
    // 1. Superbloque
    fseek(file, mountedPartition->partition.part_start, SEEK_SET);
    fwrite(&superBloque, sizeof(SuperBloque), 1, file);
    // 2. Journaling
    if (superBloque.s_filesystem_type == 3) {
        fseek(file, 100 * 64, SEEK_CUR);
        //fwrite(&journaling, sizeof(Journaling), 1, file);
    }
    // 3. Bitmap de inodos
    fwrite(&bitmapInodos, n, 1, file);
    // 4. Bitmap de bloques
    fwrite(&bitmapBloques, 3 * n, 1, file);
    // 5. Inodos
    Inodo inodo = getNewInodo();
    for (int i = 0; i < n; i++) {
        fwrite(&inodo, sizeof(Inodo), 1, file);
    }
    // 6. Bloques (Hay distintos tipos de bloque, todos de 64 bytes)
    for (int i = 0; i < 3 * n; i++) {
        fwrite("\0", 64, 1, file);
    }


    // _______________________________________ Carpeta Raiz _______________________________________

    // Creacion del bloque carpeta raiz y padre (la misma carpeta)
    BloqueDeCarpeta carpetaRaiz;
    ContentDeCarpetaArchvio contenidoCarpetaRaiz;
    strcpy(contenidoCarpetaRaiz.b_name, ".");
    contenidoCarpetaRaiz.b_inodo = 0;
    carpetaRaiz.b_content[0] = contenidoCarpetaRaiz;
    carpetaRaiz.b_content[1] = contenidoCarpetaRaiz;
    strcpy(carpetaRaiz.b_content[1].b_name, "..");

    // Creacion del inodo de la carpeta raiz y padre (la misma carpeta)
    Inodo inodoCarpetaRaiz = getNewInodo();
    inodoCarpetaRaiz.i_type = '0';
    inodoCarpetaRaiz.i_uid = 1;
    inodoCarpetaRaiz.i_gid = 1;
    inodoCarpetaRaiz.i_size = 0;
    inodoCarpetaRaiz.i_atime = time(nullptr);
    inodoCarpetaRaiz.i_ctime = inodoCarpetaRaiz.i_atime;
    inodoCarpetaRaiz.i_mtime = inodoCarpetaRaiz.i_atime;
    inodoCarpetaRaiz.i_block[0] = 0;


    // _______________________________________ Archivo Users _______________________________________

    // Bloque del archivo users
    BloqueDeArchivo archivoUsers;

    // Inodo del archivo users
    Inodo inodoArchivoUsers;
    for (int i = 0; i < 15; i++) {
        inodoArchivoUsers.i_block[i] = -1;
    }
    inodoArchivoUsers.i_uid = 1;
    inodoArchivoUsers.i_gid = 1;
    inodoArchivoUsers.i_size = 0;
    inodoArchivoUsers.i_type = '1';
    inodoArchivoUsers.i_perm = 700;
    inodoArchivoUsers.i_block[0] = 1;
    inodoArchivoUsers.i_ctime = time(nullptr);
    inodoArchivoUsers.i_mtime = inodoArchivoUsers.i_ctime;
    inodoArchivoUsers.i_atime = inodoArchivoUsers.i_ctime;

    // Se crea el contenido de la carpeta que apunta la indoo del archivo y se enlazan
    strcpy(contenidoCarpetaRaiz.b_name, "users.txt");
    contenidoCarpetaRaiz.b_inodo = 1;
    carpetaRaiz.b_content[2] = contenidoCarpetaRaiz;


    // ___________________________________ Escritura Carpeta y Archivo ___________________________________

    // Escritura de los Inodos
    escribirInodo(inodoCarpetaRaiz, 0, *mountedPartition);
    escribirInodo(inodoArchivoUsers, 1, *mountedPartition);

    // Escritura de los Bloques
    fseek(file, superBloque.s_block_start, SEEK_SET); // Mover el puntero al inicio de la tabla de bloques
    fwrite(&carpetaRaiz, 64, 1, file);
    fseek(file, 64, SEEK_CUR);
    fwrite(&archivoUsers, 64, 1, file);
    fclose(file);

    cout << "Formateo realizado con exito" << endl;
}


int Mkfs::getNumberInodos(int tamanoParticion, int tipoSistema) {
    if (tipoSistema == 2) {
        return (int)floor(((tamanoParticion - sizeof(SuperBloque)) / (1 + 3 + sizeof(Inodo) + 3 * 64)));
    } else if (tipoSistema == 3) {
        return (int)floor(((tamanoParticion - sizeof(SuperBloque) - (64 * 100)) / (1 + 3 + sizeof(Inodo) + 3 * 64)));
    } else {
        return -1;
    }
}