//
// Created by jose on 10/12/21.
//

#include "Command.h"

#ifndef MIA_PROYECTO1_201904061_MKUSER_H
#define MIA_PROYECTO1_201904061_MKUSER_H

extern Usuario usuario_montado;

class Mkuser : public Command {
public:
    vector<string> admisableParams = {"-USR", "-PWD", "-GRP"};
    vector<string> obligatoryParams = {"-USR", "-PWD", "-GRP"};
    void run() override;

    explicit Mkuser(const vector<Param> &parametros);
    string usr;
    string pwd;
    string grp;
};


#endif //MIA_PROYECTO1_201904061_MKUSER_H
