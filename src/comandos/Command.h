//
// Created by jose on 2/08/21.
//

#ifndef ARCHIVOSP1_COMMAND_H
#define ARCHIVOSP1_COMMAND_H

#include <vector>
#include <string>

#include "Param.h"

using  namespace  std;

class Command {
public:
    Command(vector<Param> params);
    virtual void run();
    bool findRepeatedParams(vector<Param> params);
    bool inadmisableParams(vector<Param> params,vector<string> admisableParams);
};

#endif //ARCHIVOSP1_COMMAND_H
