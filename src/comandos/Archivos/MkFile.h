//
// Created by jose on 28/11/21.
//

#ifndef MIA_PROYECTO1_201904061_MKFILE_H
#define MIA_PROYECTO1_201904061_MKFILE_H

#include <string>

#include "../Command.h"

class MkFile : public Command {
public:
    vector<string> admisableParams = {"-PATH", "-R", "-SIZE", "-CONT", "-STDIN", "-ID"};
    vector<string> obligatoryParams = {"-PATH", "-ID"};
    void run() override;

    explicit MkFile(vector<Param> parametros);
    string path;
    bool r;
    int size;
    string cont;
    string pStdin;
    string id;

};


#endif //MIA_PROYECTO1_201904061_MKFILE_H
