//
// Created by jose on 24/11/21.
//

#include <iostream>

#include "Login.h"

using namespace std;

Login::Login(vector<Param> parametros) : Command(parametros) {
    commandName = "LOGIN";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-USER") {
            user = quitarComillas(p.value);
        } else if (p.name == "-PWD") {
            pwd = quitarComillas(p.value);
        } else if (p.name == "-ID") {
            id = quitarComillas(p.value);
        }
    }
}

void Login::run() {
    if (!runnable) {
        return;
    }

    if (usuario.logeado) {
        cout << "Error: Debe cerrar la sesion activa para logearse." << endl;
        return;
    }

    MountedPartition* mountedPartition;
    for (auto & mp : mountedPartitions) {
        if (mp.id == id) {
            mountedPartition = &mp;
        }
    }

    if (mountedPartition == nullptr) {
        cout << "Error: No se encontro particion montada con ese id." << endl;
        return;
    }

    FILE* file =  fopen(mountedPartition->path.c_str(), "rb+");

    // Lectura de Super Bloque
    SuperBloque superBloque;
    fseek(file, mountedPartition->partition.part_start, SEEK_SET);
    fread(&superBloque, sizeof(SuperBloque), 1, file);

    // Lectura Inodo carpeta root
    Inodo inodo_carpeta_root;
    fseek(file, superBloque.s_inode_start, SEEK_SET);        // Mover el puntero al inicio de la tabla de inodos
    fread(&inodo_carpeta_root, sizeof(Inodo), 1, file);   // Leer el inodo

    // Lectura del bloque de carpeta root
    BloqueDeCarpeta bloque_carpeta_root;
    fseek(file, superBloque.s_block_start, SEEK_SET);                   // Mover el puntero al inicio de la tabla de inodos
    fread(&bloque_carpeta_root, sizeof(BloqueDeCarpeta), 1, file);   // Leer el inodo

    // Lectura bloque
    BloqueDeArchivo bloqueUsuarios;
    fseek(file, superBloque.s_block_start, SEEK_SET);  // Mover el puntero al inicio de la tabla de bloques
    fseek(file, 64, SEEK_CUR);                     // Mover el puntero al segundo bloque que corresponde al archivo de users.txt
    fread(&bloqueUsuarios, sizeof(BloqueDeArchivo), 1, file); // Leer el bloque
    fclose(file);








    cout << "Se ha inidciado seccion con exito" << endl;
}

