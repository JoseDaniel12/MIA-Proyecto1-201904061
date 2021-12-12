//
// Created by jose on 29/11/21.
//

#ifndef MIA_PROYECTO1_201904061_MKDIR_H
#define MIA_PROYECTO1_201904061_MKDIR_H

#include "Command.h"

extern Usuario usuario_montado;

class Mkdir : public Command {
public:
    vector<string> admisableParams = {"-PATH", "-P"};
    vector<string> obligatoryParams = {"-PATH"};
    void run() override;

    explicit Mkdir(const vector<Param> &parametros);
    string path;
    bool param_p;
};


#endif //MIA_PROYECTO1_201904061_MKDIR_H
