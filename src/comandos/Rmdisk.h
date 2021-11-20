//
// Created by jose on 9/08/21.
//

#ifndef MIA_PROYECTO1_201904061_RMDISK_H
#define MIA_PROYECTO1_201904061_RMDISK_H

#include "Command.h"

class Rmdisk : public Command  {
public:
    vector<string> admisableParams = {"-PATH"};
    vector<string> obligatoryParams = {"-PATH"};
    void run() override;

    explicit Rmdisk(const vector<Param>& parametros);
    string path;

};


#endif //MIA_PROYECTO1_201904061_RMDISK_H
