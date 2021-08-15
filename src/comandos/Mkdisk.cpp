//
// Created by jose on 5/08/21.
//

#include "Mkdisk.h"

#include <iostream>
#include <vector>
#include <string>
#include<string.h>

#include "../structs.h"


using namespace std;

Mkdisk::Mkdisk(const vector<Param>& parametros):Command(parametros) {
    commandName = "MKDISK";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-SIZE") {
            size = stoi(p.value);
        } else if (p.name == "-F") {
            f = p.value.c_str()[0];
        } else if (p.name == "-U") {
            u = p.value.c_str()[0];
        } else if (p.name == "-PATH") {
            path = rootPath + quitarComillas(p.value);
        }
    }

}

void Mkdisk::run() {
    if (!runnable) {
        return;
    }
    char pathChars[path.size() + 1];
    strcpy(pathChars, path.c_str());
    FILE* file  = nullptr;
    file = fopen(pathChars, "r");
    if (file != nullptr) {
        cout << "Error: Ya existe el disco." << endl;
        return;
    }

    int tam = 0;
    if (u == 'K') {
        tam  = size * 1024;
    } else if (u == 'M') {
        tam = size * 1024  * 1024;
    }

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

    MBR mbr;
    mbr.mbr_tamano = tam;
    mbr.mbr_fecha_creacion = time(0);
    mbr.mbr_disk_signature =  static_cast<int>(time(nullptr));
    mbr.disk_fit = f;
    for (auto & i : mbr.mbr_partition) {
        i.part_status = '0';
        i.part_size = 0;
        i.part_fit = 'f';
        i.part_start = tam;
        strcpy(i.part_name,"");
    }

    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, file);
    fclose(file);

    cout << "Disco creado con exito:" << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fecha de creacion: " << asctime(gmtime(&mbr.mbr_fecha_creacion));
    cout << "Signature: " << mbr.mbr_disk_signature << endl;
    cout << "Fit: " << mbr.disk_fit << endl;
}