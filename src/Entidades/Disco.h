//
// Created by jose on 23/08/21.
//

#ifndef MIA_PROYECTO1_201904061_DISCO_H
#define MIA_PROYECTO1_201904061_DISCO_H

#include <string>
#include <vector>

#include "../structs.h"
#include "../comandos/Command.h"

using namespace std;

class Disco {
public:
    string path;
    explicit Disco(string pathDisco);
    [[nodiscard]] bool existeDisco() const;
    bool getMBR(MBR* destino) const;
    [[nodiscard]] vector<Partition> getNonLogialPartitions() const;
    [[nodiscard]] vector<Partition> getPrimaryPartitions() const;
    bool getExtendedPartition(Partition* destino) const;
    [[nodiscard]] vector<EBR> getEbrs() const;
    [[nodiscard]] vector<Partition> getLogicalPartitions() const;
    [[nodiscard]] vector<PartitionHole> getLogicalHoles() const;
    bool getPartitionByName(Partition* destino, const string& nombre) const;
    void generarReporteDisco(const string& directory, const string& fileName, const string& extension) const;
    void generarReporteMbr(const string& directory, const string& fileName, const string& extension) const;
    [[nodiscard]] vector<PartitionHole> getNotLogicalHoles() const;
    static string truncar(float numero);
};

#endif //MIA_PROYECTO1_201904061_DISCO_H
