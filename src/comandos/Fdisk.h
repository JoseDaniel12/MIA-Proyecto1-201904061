//
// Created by jose on 10/08/21.
//

#ifndef MIA_PROYECTO1_201904061_FDISK_H
#define MIA_PROYECTO1_201904061_FDISK_H


#include "Command.h"
#include "../structs.h"
class Fdisk : public Command {
public:
    vector<string> admisableParams = {"-SIZE", "-UNIT", "-PATH", "-TYPE", "-FIT", "-DELETE", "-NAME", "-ADD"};
    vector<string> obligatoryParams = {"-PATH", "-NAME"};
    virtual void run() override;

    Fdisk(const vector<Param>& parametros);
    static vector<PartitionHole> getNotLogicalHoles(MBR mbr);
    static vector<PartitionHole> getLogicalHoles(vector<EBR> ebrs, int startPartition, int endPartition);
    [[nodiscard]] int getSartPartition(vector<PartitionHole> holes, char diskFit) const;
    void createNonLogicalPartition();
    void createLogicalPartition();
    static void orderPartitions(Partition parts[4]);
    static vector<EBR> orderEbrs(vector<EBR> ebrs);
    void deletePartition() const;
    void changeSpacePartition() const;
    bool isCreate = false;
    bool isDelete = false;
    bool isAdd = false;
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
