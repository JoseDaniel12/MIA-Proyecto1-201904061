//
// Created by jose on 14/12/21.
//

#ifndef MIA_PROYECTO1_201904061_FIND_H
#define MIA_PROYECTO1_201904061_FIND_H

#include "Command.h"

extern Usuario usuario_montado;

class Find : public Command  {
public:
    vector<string> admisableParams = {"-PATH", "-NAME"};
    vector<string> obligatoryParams = {"-PATH", "-NAME"};
    virtual void run() override;
    string path;
    string name;

    Find(const vector<Param>& params);
};


#endif //MIA_PROYECTO1_201904061_FIND_H
