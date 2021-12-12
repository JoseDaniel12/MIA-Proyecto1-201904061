//
// Created by jose on 28/11/21.
//

#ifndef MIA_PROYECTO1_201904061_MKFILE_H
#define MIA_PROYECTO1_201904061_MKFILE_H

#include <string>

#include "../Command.h"

extern Usuario usuario_montado;

class MkFile : public Command {
public:
    vector<string> admisableParams = {"-PATH", "-R", "-SIZE", "-CONT", "-STDIN"};
    vector<string> obligatoryParams = {"-PATH"};
    void run() override;

    explicit MkFile(vector<Param> parametros);
    string path;
    bool r;
    int size = 0;
    string cont;
    bool pStdin = false;
};


#endif //MIA_PROYECTO1_201904061_MKFILE_H
