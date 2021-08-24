//
// Created by jose on 24/08/21.
//

#include <iostream>

#include "Umount.h"

using namespace std;


Umount::Umount(vector<Param> parametros):Command(parametros) {
    commandName = "UMOUNT";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-ID") {
            id = p.value;
        }
    }
}

void Umount::run() {
    if (!runnable) {
        return;
    }

    bool encontrada = false;
    int contador = 0;
    for (auto & mp : mountedPartitions) {
        if (mp.id == id) {
            cout << "La particion desmonatada tenia los iguientes datos: " << endl;
            cout << "Part_status: " << mp.partition.part_status << endl;
            cout << "Part_type: " << mp.partition.part_type << endl;
            cout << "Part_fit: " << mp.partition.part_fit << endl;
            cout << "Part_start: " << mp.partition.part_start << endl;
            cout << "Part_size: " << mp.partition.part_size << endl;
            cout << "Part_name: " << mp.partition.part_name << endl;
            mountedPartitions.erase(mountedPartitions.cbegin() + contador);
            encontrada = true;
        }
        contador++;
    }

    if (!encontrada) {
        cout << "Error: no se econtro la particion a desmontar." << endl;
    }

}