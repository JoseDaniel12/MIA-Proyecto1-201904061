//
// Created by jose on 5/08/21.
//

#include "Mkdisk.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>

#include "../structs.h"


using namespace std;

Mkdisk::Mkdisk(const vector<Param>& parametros):Command(parametros) {
    // Se establece el nombre del comando y se verifica si falstan o sobran parametros
    commandName = "MKDISK";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    // En caso de no haber errores aparentes en los parametros estos se recogen
    for (const Param& p: parametros) {
        if (p.name == "-SIZE") {
            size = stoi(p.value);
        } else if (p.name == "-FIT") {
            f = (char) toupper(p.value.c_str()[0]);
        } else if (p.name == "-UNIT") {
            u = (char) toupper(p.value.c_str()[0]);
        } else if (p.name == "-PATH") {
            path = rootPath + quitarComillas(p.value);
        }
    }

}

void Mkdisk::run() {
    // En caso de haber errores no se va ejecutar el comando
    if (!runnable) {
        return;
    }

    if (size < 0) {
        cout << "Error: el parametro -size debe ser mayor que cero" << endl;
        return;
    }

    // Se abre el archivo del path y en caso de no existir marca error
    char pathChars[path.size() + 1];
    strcpy(pathChars, path.c_str());
    FILE* file;
    file = fopen(pathChars, "r");
    if (file != nullptr) {
        cout << "Error: Ya existe el disco." << endl;
        return;
    }

    // Se guarda el tamaño del disco en bytes, si no tiene una unidad valida marcara error
    int tam;
    if (u == 'K') {
        tam  = size * 1024;
    } else if (u == 'M') {
        tam = size * 1024  * 1024;
    } else {
        cout << "Error el parametro -u no dene ser k(kiloytes) o m(megabytes)." << endl;
        return;
    }

    // En caso de que no exista el directorio del archivo se cre y luego se cra el archivo tambien
    file = fopen(pathChars, "wb");
    if (file == nullptr) {
        string dir = getDirectory(path);
        string comando = "mkdir -p \'" + dir +"\'";
        system(comando.c_str());
        file = fopen(pathChars, "wb");
    }
    fwrite("\0", 1, 1, file);
    fseek(file,tam,SEEK_SET);
    fwrite("\0", 1, 1, file);

    // Se inicializa el MBR
    MBR mbr;
    mbr.mbr_tamano = tam;
    mbr.mbr_fecha_creacion = time(nullptr);
    mbr.mbr_disk_signature =  static_cast<int>(time(nullptr));
    mbr.disk_fit = f;
    for (auto & i : mbr.mbr_partition) {
        i.part_status = '0';
        i.part_type = 'N';
        i.part_fit = 'F';
        i.part_start = tam;
        i.part_size = 0;
        strcpy(i.part_name,"");
    }

    // Se escribe escribe el MBR en el disco simulado
    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, file);
    fclose(file);

    // Se escribe en el resto del disco 0's
//    int vacio;
//    fseek(file, sizeof(MBR), SEEK_SET);
//    fwrite(&vacio, sizeof(vacio), mbr.mbr_tamano - sizeof(MBR) + 1, file);

    // Se imprime la inforacmacion para ver que el comando se ejecutara correctamente
    cout << "Disco creado con exito:" << endl;
    cout << "Fecha de creacion: " << asctime(gmtime(&mbr.mbr_fecha_creacion));
    cout << "Tamaño: " << mbr.mbr_tamano << " bytes" << endl;
    cout << "Signature: " << mbr.mbr_disk_signature << endl;
    cout << "Fit: " << mbr.disk_fit << endl;
}