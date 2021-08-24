//
// Created by jose on 23/08/21.
//

#include <utility>
#include <vector>
#include <cstring>

#include "Disco.h"

Disco::Disco(string pathDisco) {
    path = std::move(pathDisco);
}

bool Disco::existeDisco() const {
    FILE* file = fopen(path.c_str(), "rb+");
    fclose(file);
    if (file == nullptr) {
        return false;
    }
    return true;
}

bool Disco::getMBR(MBR* destino) const {
    FILE* file = fopen(path.c_str(), "rb+");
    if  (file != nullptr) {
        MBR mbr;
        fseek(file,0,SEEK_SET);
        fread(&mbr, sizeof(MBR), 1, file);
        *destino = mbr;
        return true;
    }
    return false;
}


vector<Partition> Disco::getNonLogialPartitions() const {
    vector<Partition> partitions;
    MBR mbr;
    if (getMBR(&mbr)) {
        for (auto & p : mbr.mbr_partition) {
            partitions.push_back(p);
        }
    }
    return partitions;
}

bool Disco::getExtendedPartition(Partition* destino) const {
    vector<Partition> partitions = getNonLogialPartitions();
    for (auto &p : partitions)
        if (p.part_type == 'E') {
            *destino = p;
            return true;
        }
    return false;
}

vector<EBR> Disco::getEbrs() const {
    FILE* file = fopen(path.c_str(), "rb+");
    vector<EBR> ebrs;
    MBR mbr;
    getMBR(&mbr);
    Partition extendedPartition;
    getExtendedPartition(&extendedPartition);
    EBR ebr;
    fseek(file, extendedPartition.part_start, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, file);
    ebrs.push_back(ebr);
    while (ebr.part_next != -1) {
        EBR nextEbr;
        fseek(file, ebr.part_next, SEEK_SET);
        fread(&nextEbr, sizeof(EBR), 1, file);
        ebrs.push_back(nextEbr);
        ebr = nextEbr;
    }
    return ebrs;
}

vector<Partition> Disco::getLogicalPartitions() const {
    vector<Partition> partitions;
    vector<EBR> ebrs = getEbrs();
    for (auto & e : ebrs) {
        if (e.part_status == '1') {
            Partition p;
            p.part_status = e.part_status;
            p.part_type = 'L';
            p.part_fit = e.part_fit;
            p.part_start = e.part_start;
            p.part_size = e.part_size;
            strcpy(p.part_name, e.part_name);
            partitions.push_back(p);
        }
    }
    return partitions;
}

bool Disco::getPartitionByName(Partition* destino, const string& nombre) const {
    vector<Partition> nonLogicalPartitions = getNonLogialPartitions();
    vector<Partition> logicalPartitions = getLogicalPartitions();
    vector<Partition> partitions;
    partitions.insert(partitions.end(), nonLogicalPartitions.begin(), nonLogicalPartitions.end());
    partitions.insert(partitions.end(), logicalPartitions.begin(), logicalPartitions.end());
    for (auto & p : partitions) {
        if (p.part_name == nombre) {
            *destino = p;
            return true;
        }
    }
    return false;
}
