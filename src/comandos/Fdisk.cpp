//
// Created by jose on 10/08/21.
//

#include <cstring>
#include <iostream>

#include "Fdisk.h"

using namespace std;

Fdisk::Fdisk(const vector<Param> &parametros): Command(parametros) {
    commandName = "FDISK";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }
    if (getParamPos(parametros, "-SIZE") == -1 && getParamPos(parametros, "-DELETE") == -1) {
        runnable = false;
        return;
    }
    if (getParamPos(parametros, "-SIZE") != -1 && getParamPos(parametros, "-DELETE") != -1) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-SIZE") {
            size = stoi(p.value);
            create = true;
        } else if (p.name == "-U") {
            u = p.value.c_str()[0];
        } else if (p.name == "-PATH") {
            path = rootPath + quitarComillas(p.value);
        } else if (p.name == "-TYPE") {
            type = p.value.c_str()[0];
        }  else if (p.name == "-F") {
            f = p.value.c_str()[0];
        } else if (p.name == "-DELETE") {
            pdelete = p.value;
        } else if (p.name == "-NAME") {
            name  = p.value;
        } else if (p.name == "-ADD") {
            add = stoi(p.value);
        }
    }

}

void Fdisk::run() {
    if (!runnable) {
        return;
    }

    if (create) {
        if (type == 'P' || type == 'E') {
            createNonLogicalPartition();
        } else if (type == 'L') {
            createLogicalPartition();
        }
    } else {

    }

}

void Fdisk::createNonLogicalPartition() {
    //Verifica si el disco existe y de ser asi obtiene el mbr
    int sizeBytes =  convertToBytes(size, u);
    MBR mbr;
    FILE* file = fopen(path.c_str(), "rb+");
    if (file == nullptr) {
        cout << "Error: No existe el disco." << endl;
        return;
    }
    fseek(file, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, file);

    //Verifica que el numero de tipo de la particion a crear sea el correcto
    int numPrimarias = 0;
    int numExtendias = 0;
    if (type == 'P' || type == 'E') {
        for (auto & parition : mbr.mbr_partition) {
            if (parition.part_status == '1') {
                if (parition.part_type == 'P') {
                    numPrimarias++;
                } else if (parition.part_type == 'E') {
                    numExtendias++;
                }
            }
        }
        if (numExtendias + numPrimarias == 4) {
            cout << "Error: El disco ya cuenta con 4 particions" << endl;
            return;
        }  else if (type == 'E') {
            if (numExtendias == 1) {
                cout << "Error: Ya existe una particion extendida." << endl;
                return;
            }
        }
    }

    //Verifica que haya espacio diponible el disco para la nueva particion
    int espacioUtilizado = 0;
    for (auto & partition : mbr.mbr_partition) {
        if (partition.part_status == '1') {
            espacioUtilizado += partition.part_size;
        }
    }
    if (mbr.mbr_tamano - espacioUtilizado < sizeBytes) {
        cout << "Error: No hay espacio suficiente para hacer la particion en el disco." << endl;
        return;
    }


    //Verifica que el nombre no exista en la otras particiones
    for (auto & partition : mbr.mbr_partition) {
        if (partition.part_name == name) {
            cout << "Error: Ya existe una particon con ese nombre." << endl;
            return;
        }
    }

    //Se establece en cual de las 4 particiones inciara la nueva patricion segun el fit del mbr
    Partition* particionSeleccionada;
    for (auto & partition : mbr.mbr_partition) {
        if (partition.part_status == '0') {
            particionSeleccionada = &partition;
            break;
        }
    }

    //Se llenan los datos de la particion
    int startByte = getSartPartition(getNotLogicalHoles(mbr), mbr.disk_fit);
    if (startByte == -1) {
        cout << "Error: Vacios muy pequeños para crear la particion." << endl;
        return;
    }
    particionSeleccionada->part_status = '1';
    particionSeleccionada->part_type = type;
    particionSeleccionada->part_fit = f;
    particionSeleccionada->part_start = startByte;
    particionSeleccionada->part_size = sizeBytes;
    strcpy(particionSeleccionada->part_name, name.c_str());
    orderPartitions(mbr.mbr_partition);

    //Se guarda la nueva informacion
    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof(MBR), 1, file);
    fclose(file);

    cout << "Particion creada con exito:" << endl;
    cout << "Part_status: " << particionSeleccionada->part_status << endl;
    cout << "Part_type: " << particionSeleccionada->part_type << endl;
    cout << "Part_fit: " << particionSeleccionada->part_fit << endl;
    cout << "Part_start: " << particionSeleccionada->part_start << endl;
    cout << "Part_size: " << particionSeleccionada->part_size << endl;
    cout << "Part_name: " << particionSeleccionada->part_name << endl;

}

void Fdisk::createLogicalPartition() {}

void Fdisk::orderPartitions(Partition partitions[4]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - j; j++) {
            if (partitions[j].part_size > partitions[j + 1].part_size || partitions[j].part_status == '0') {
                Partition temp =  partitions[j];
                partitions[j] = partitions[j + 1];
                partitions[j + 1] = temp;
            }
        }
    }
}

vector<PartitionHole> Fdisk::getNotLogicalHoles(MBR mbr) {
    int start = sizeof(MBR);
    int end = mbr.mbr_tamano;

    vector<PartitionHole> holes;
    int numActivePartitions = 0;
    for (auto & partition : mbr.mbr_partition) {
        if (partition.part_status == '1') {
            numActivePartitions++;
        }
    }

    if (numActivePartitions == 0) {
        PartitionHole hole;
        hole.start = sizeof(MBR);
        hole.size = mbr.mbr_tamano - hole.start;
        holes.push_back(hole);
        return holes;
    }

    int revisado = 0;
    for (int i = 0; i < 4 - 1; i++) {
        if (mbr.mbr_partition[i].part_status == '1') {
            revisado++;
            int nextIndex = i + 1;
            while (mbr.mbr_partition[nextIndex].part_status == '1' && nextIndex < 4) {
                if (mbr.mbr_partition[nextIndex].part_start - (mbr.mbr_partition[i].part_start + mbr.mbr_partition[i].part_size) != 0) {
                    PartitionHole hole;
                    hole.start = mbr.mbr_partition[i].part_start + mbr.mbr_partition[i].part_size;
                    hole.size = mbr.mbr_partition[nextIndex].part_start - hole.start;
                    holes.push_back(hole);
                } else {
                    break;
                }
                nextIndex++;
            }
            if (revisado == 1 && mbr.mbr_partition[revisado - 1].part_start != start) {
                PartitionHole hole;
                hole.start = start;
                hole.size = mbr.mbr_partition[revisado - 1].part_start - start;
                holes.push_back(hole);
            } else if (revisado == numActivePartitions && mbr.mbr_partition[revisado - 1].part_start + mbr.mbr_partition[revisado - 1].part_size != end) {
                PartitionHole hole;
                hole.start = mbr.mbr_partition[revisado - 1].part_start + mbr.mbr_partition[revisado - 1].part_size;
                hole.size = end - hole.start;
                holes.push_back(hole);
            }
        }
    }
    return holes;
}

int Fdisk::getSartPartition(vector<PartitionHole> holes, char diskFit) const {
    if (!holes.empty()) {
        int holeIndex = 0;
        for (int i = 0; i < holes.size(); i++) {
            if (holes[i].size >= size) {
                if ((diskFit == 'B' && holes[i].size < holes[holeIndex].size) || (diskFit == 'W' && holes[i].size > holes[holeIndex].size)) {
                    holeIndex = i;
                } else if (diskFit == 'F') {
                    return holes[i].start;
                }
            }
        }
        if (holes[holeIndex].size >= size) {
            return holes[holeIndex].start;
        }
    }
    cout << "Error: No hay vacios con el espacio nesesario para crear la particion." << endl;
    return -1;
}