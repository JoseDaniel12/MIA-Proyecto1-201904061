//
// Created by jose on 29/08/21.
//

#ifndef MIA_PROYECTO1_201904061_REP_H
#define MIA_PROYECTO1_201904061_REP_H


#include "Command.h"
#include "../structs.h"

extern vector<MountedPartition> mountedPartitions;

class Rep : public Command {
public:
    vector<string> admisableParams = {"-NAME", "-PATH", "-ID", "-RUTA", "-ROOT"};
    vector<string> obligatoryParams = {"-NAME", "-PATH", "-ID"};
    virtual void run() override;

    Rep(const vector<Param>& params);
    string name;
    string path;
    string id;
    string ruta;
    int root;

};

#endif //MIA_PROYECTO1_201904061_REP_H
