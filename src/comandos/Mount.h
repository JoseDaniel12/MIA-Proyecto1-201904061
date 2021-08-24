//
// Created by jose on 22/08/21.
//

#ifndef MIA_PROYECTO1_201904061_MOUNT_H
#define MIA_PROYECTO1_201904061_MOUNT_H

#include "Command.h"
#include "../structs.h"


extern vector<MountedPartition> mountedPartitions;

class Mount : public Command {
public:
    vector<string> admisableParams = {"-PATH", "-NAME"};
    vector<string> obligatoryParams = {"-PATH", "-NAME"};
    void run() override;

    explicit Mount(const vector<Param>& parametros);
    string path;
    string name;
    string getMountedPartitionId() const;
};


#endif //MIA_PROYECTO1_201904061_MOUNT_H
