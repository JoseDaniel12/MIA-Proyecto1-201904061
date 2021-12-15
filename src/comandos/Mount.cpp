//
// Created by jose on 22/08/21.
//

#include <iostream>
#include <map>

#include "Mount.h"
#include "../Entidades/Disco.h"

using namespace std;

Mount::Mount(const vector<Param> &parametros): Command(parametros) {
    commandName = "MOUNT";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-PATH") {
            path = rootPath + quitarComillas(p.value);
        } else if (p.name == "-NAME") {
            name  = p.value;
        }
    }
}

void Mount::run() {
    if (!runnable) {
        return;
    }

    Disco disco = *new Disco(path);
    Partition partitionToMount;
    if (!disco.existeDisco()) {
        cout << "Error: no existe el disco." << endl;
        return;
    } else {
        for (auto & p : mountedPartitions) {
            if(p.partition.part_name == name) {
                cout << "Error: la particion ya se encuentra montada." << endl;
                return;
            }
        }
        if (disco.getPartitionByName(&partitionToMount, name)) {
            cout << "Particon monatad con exito con los siguientes datos:" << endl;
            cout << "Part_status: " << partitionToMount.part_status << endl;
            cout << "Part_type: " << partitionToMount.part_type << endl;
            cout << "Part_fit: " << partitionToMount.part_fit << endl;
            cout << "Part_start: " << partitionToMount.part_start << endl;
            cout << "Part_size: " << partitionToMount.part_size << endl;
            cout << "Part_name: " << partitionToMount.part_name << endl;
            MountedPartition newMounted;
            newMounted.id = getMountedPartitionId();
            newMounted.path = path;
            newMounted.partition = partitionToMount;
            mountedPartitions.push_back(newMounted);
            cout << "Las particiones actualemente montadas son:" << endl;
            for (auto & p : mountedPartitions) {
                cout << p.path << " | " << p.partition.part_name << " | " << p.id << endl;
            }
        } else {
            cout << "Error: no se encontro la particion" << endl;
            return;
        }
    }
}

string Mount::getMountedPartitionId() const {
    vector<char> abcdario = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                              'r', 's', 'u', 'v', 'w', 'x', 'y', 'z' };
    string id = "vd";
    char letra;
    map<string, int> registroNumParticiones; // path, numero de veces que sale ese path (cantidad de particiones)
    for (auto & mp : mountedPartitions) {
        if (registroNumParticiones[mp.path] == false) {
            registroNumParticiones[mp.path] = 1;
        } else {
            registroNumParticiones[mp.path] += 1;
        }
    }
    if ( registroNumParticiones[path] == false) {
        registroNumParticiones[path] = 1;
    } else {
        registroNumParticiones[path] += 1;
    }
    letra = abcdario[(registroNumParticiones[path] <= abcdario.size()? registroNumParticiones[path] : registroNumParticiones[path] -  abcdario.size()) - 1];
    bool encontrado;
    int cont = 0;
    for ( const auto &pair : registroNumParticiones ) {
        if (path == pair.first) {
            encontrado = true;
            break;
        }
        cont++;
    }

    return id + letra + to_string((encontrado ? cont : registroNumParticiones.size()) + 1);
}