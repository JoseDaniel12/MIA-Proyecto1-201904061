//
// Created by jose on 10/12/21.
//

#ifndef MIA_PROYECTO1_201904061_MKGRP_H
#define MIA_PROYECTO1_201904061_MKGRP_H

#include "Command.h"
#include "../structs.h"

extern Usuario usuario_montado;

class Mkgrp : public Command {
public:
    vector<string> admisableParams = {"-NAME"};
    vector<string> obligatoryParams = {"-NAME"};
    void run() override;

    Mkgrp(vector<Param> parametros);
    string name;
};


#endif //MIA_PROYECTO1_201904061_MKGRP_H
