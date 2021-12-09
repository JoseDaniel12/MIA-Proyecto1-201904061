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
    vector<string> admisableParams = {"-ID", "-TYPE", "-FS"};
    vector<string> obligatoryParams = {"-ID"};
    void run() override;

    explicit Mkfs(const vector<Param> &parametros);
    int getNumberInodos(int tamanoParticion, int tipoSistema);
    string id;
    string type;
    string fs;
};


#endif //MIA_PROYECTO1_201904061_MKFS_H
