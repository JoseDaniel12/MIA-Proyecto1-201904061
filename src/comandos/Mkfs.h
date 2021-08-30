//
// Created by jose on 24/08/21.
//

#ifndef MIA_PROYECTO1_201904061_MKFS_H
#define MIA_PROYECTO1_201904061_MKFS_H


#include "Command.h"

class Mkfs : public Command {
public:
    vector<string> admisableParams = {"-SIZE", "-U", "-PATH", "-TYPE", "-F", "-DELETE", "-NAME", "-ADD"};
    vector<string> obligatoryParams = {"-PATH", "-NAME"};
    void run() override;

    explicit Mkfs(const vector<Param> &parametros);

};


#endif //MIA_PROYECTO1_201904061_MKFS_H
