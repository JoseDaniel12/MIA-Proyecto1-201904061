//
// Created by jose on 23/08/21.
//

#ifndef MIA_PROYECTO1_201904061_DISCO_H
#define MIA_PROYECTO1_201904061_DISCO_H

#include <string>
#include <vector>

#include "../structs.h"

using namespace std;

class Disco {
public:
    string path;
    explicit Disco(string pathDisco);
    [[nodiscard]] bool existeDisco() const;
    bool getMBR(MBR* destino) const;
    [[nodiscard]] vector<Partition> getNonLogialPartitions() const;
    bool getExtendedPartition(Partition* destino) const;
    [[nodiscard]] vector<EBR> getEbrs() const;
    [[nodiscard]] vector<Partition> getLogicalPartitions() const;
    bool getPartitionByName(Partition* destino, const string& nombre) const;
};


#endif //MIA_PROYECTO1_201904061_DISCO_H
