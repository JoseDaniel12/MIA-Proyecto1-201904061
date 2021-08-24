//
// Created by jose on 24/08/21.
//

#ifndef MIA_PROYECTO1_201904061_UMOUNT_H
#define MIA_PROYECTO1_201904061_UMOUNT_H


#include "Command.h"
#include "../structs.h"

extern vector<MountedPartition> mountedPartitions;

class Umount : public Command {
public:
    vector<string> admisableParams = {"-ID"};
    vector<string> obligatoryParams = {"-ID"};
    void run() override;

    Umount(vector<Param> params);
    string id;
};


#endif //MIA_PROYECTO1_201904061_UMOUNT_H
