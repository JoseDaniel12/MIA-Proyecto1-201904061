//
// Created by jose on 24/11/21.
//

#ifndef MIA_PROYECTO1_201904061_LOGIN_H
#define MIA_PROYECTO1_201904061_LOGIN_H

#include <string>

#include "../Command.h"
#include "../../structs.h"

extern vector<MountedPartition> mountedPartitions;
extern Usuario usuario;

class Login : public Command {
public:
    vector<string> admisableParams = {"-USR", "-PWD", "-ID"};
    vector<string> obligatoryParams = {"-USR", "-PWD", "-ID"};
    void run() override;

    Login(vector<Param> params);
    string user;
    string pwd;
    string id;
};


#endif //MIA_PROYECTO1_201904061_LOGIN_H
