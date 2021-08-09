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
    bool correctParams = !inadmisableParams(parametros, {"-size", "-f", "-u", "-path"});
    if (correctParams) {
        for (const Param& p: parametros) {
            if (p.name == "-size") {
                size = stoi(p.value);
            } else if (p.name == "-f") {
                char char_array[p.value.size() + 1];
                strcpy(char_array, p.value.c_str());
                f = char_array[0];
            } else if (p.name == "-u") {
                char char_array[p.value.size() + 1];
                strcpy(char_array, p.value.c_str());
                u = char_array[0];
            } else if (p.name == "-path") {
                path = p.value;
            }
        }
    }
}

void Mkdisk::run() {
    char pathChars[path.size() + 1];
    strcpy(pathChars, path.c_str());
    FILE* file  = nullptr;
    file = fopen(pathChars, "r");
    if (file != nullptr) {
        cout << "Ya existe el disco." << endl;
        return;
    }

    int tam = 0;
    if (u == 'K') {
        tam  = size * 1024;
    } else if (u == 'm') {
        tam = size * 1024  * 1024;
    }

    file = fopen(pathChars, "wb");
    fwrite("\0", 1, 1, file);
    fseek(file,tam,SEEK_SET);
    fwrite("\0", 1, 1, file);

    MBR mbr;
    mbr.mbr_tamano = tam;
    mbr.mbr_disk_signature =  static_cast<int>(time(nullptr));
    mbr.mbr_fecha_creacion = time(0);
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

    cout << "-------------DISCO CREADO--------------------" << endl;
    cout << "Fecha de creacion: " << asctime(gmtime(&mbr.mbr_fecha_creacion)) << endl;
    cout << "Signature: " << mbr.mbr_disk_signature << endl;
    cout << "Tamaño: " << mbr.mbr_tamano << endl;
    cout << "Fit: " << mbr.disk_fit << endl;
}