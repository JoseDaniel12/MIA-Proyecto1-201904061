//
// Created by jose on 10/08/21.
//

#ifndef MIA_PROYECTO1_201904061_FDISK_H
#define MIA_PROYECTO1_201904061_FDISK_H


#include "Command.h"
#include "../structs.h"

class Fdisk : public Command {
public:
    vector<string> admisableParams = {"-SIZE", "-U", "-PATH", "-TYPE", "-F", "-DELETE", "-NAME", "-ADD"};
    vector<string> obligatoryParams = {"-PATH", "-NAME"};
    virtual void run() override;

    Fdisk(const vector<Param>& parametros);
    static vector<PartitionHole> getNotLogicalHoles(MBR mbr);
    [[nodiscard]] int getSartPartition(vector<PartitionHole> holes, char diskFit) const;
    void createNonLogicalPartition();
    void createLogicalPartition();
    static void orderPartitions(Partition parts[4]);
    void deletePartition();
    bool create = false;
    int size;
    char u = 'K';
    string path;
    char type = 'P';
    char f = 'W';
    string pdelete;
    string name;
    int add;
};


#endif //MIA_PROYECTO1_201904061_FDISK_H
