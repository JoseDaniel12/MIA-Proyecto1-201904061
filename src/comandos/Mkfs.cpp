//
// Created by jose on 24/08/21.
//

#include <iostream>
#include <math.h>

#include "Mkfs.h"

using namespace std;

Mkfs::Mkfs(const vector<Param> &parametros):Command(parametros) {
    commandName = "MKFS";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-ID") {
            id = p.value;
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

    // Se obtiene la particion montada a aplicarle el sitema de archivos
    Partition* particion;
    for (auto & mp : mountedPartitions) {
        if (mp.id == id) {
            if (mp.partition.part_type == 'P' || mp.partition.part_type == 'L') {
                particion = &mp.partition;
            } else {
                cout << "Error: Solo se puede montar un sistema de archivos en una partición primaria o lógica." << endl;
                return;
            }
        }
    }

    // Se verifica que se haya encontrado una paritcion montada para establecerle el sistema de archivos
    if (particion == nullptr) {
        cout << "Error: No se encontro particion montada con ese id." << endl;
        return;
    }

    SuperBloque superBloque;
    superBloque.s_filesystem_type = (fs == "EXT3")? 3 : 2;
    superBloque.s_inodes_count = 1;



    cout << "Formateo realizado con exito" << endl;
}


int getNumberInodos(int tamanoParticion, int tipoSistema) {
    if (tipoSistema == 2) {
        return (int)floor(((tamanoParticion - sizeof(SuperBloque)) / (1 + 3 + sizeof(TablaInodos) + 3 * 64)));
    } else if (tipoSistema == 3) {
        return (int)floor(((tamanoParticion - sizeof(SuperBloque) - 6400) / (1 + 3 + sizeof(TablaInodos) + 3 * 64)));
    } else {
        return 0;
    }
}