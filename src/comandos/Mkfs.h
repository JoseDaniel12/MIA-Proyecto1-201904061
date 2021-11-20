//
// Created by jose on 24/08/21.
//

#ifndef MIA_PROYECTO1_201904061_MKFS_H
#define MIA_PROYECTO1_201904061_MKFS_H

#include <string>

#include "Command.h"
#include "../structs.h"

extern vector<MountedPartition> mountedPartitions;

class Mkfs : public Command {
public:
    vector<string> admisableParams = {"-SIZE", "-U", "-PATH", "-TYPE", "-F", "-DELETE", "-NAME", "-ADD"};
    vector<string> obligatoryParams = {"-PATH", "-NAME"};
    void run() override;

    explicit Mkfs(const vector<Param> &parametros);
    string id;
    string type;
    string fs;

};


#endif //MIA_PROYECTO1_201904061_MKFS_H
