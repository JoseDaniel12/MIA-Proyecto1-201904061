//
// Created by jose on 11/12/21.
//

#ifndef MIA_PROYECTO1_201904061_LOGOUT_H
#define MIA_PROYECTO1_201904061_LOGOUT_H

#include "Command.h"

extern Usuario usuario_montado;

class Logout : public Command {
public:
    vector<string> admisableParams = {};
    vector<string> obligatoryParams = {};
    void run() override;

    Logout(vector<Param> parametros);
};


#endif //MIA_PROYECTO1_201904061_LOGOUT_H
