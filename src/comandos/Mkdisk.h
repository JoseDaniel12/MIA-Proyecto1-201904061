//
// Created by jose on 5/08/21.
//

#ifndef MIA_PROYECTO1_201904061_MKDISK_H
#define MIA_PROYECTO1_201904061_MKDISK_H

#include "Command.h"

#include <string>
#include <vector>

using namespace std;

class Mkdisk: public Command {
public:
    vector<string> admisableParams = {"-SIZE", "-FIT", "-UNIT", "-PATH"};
    vector<string> obligatoryParams = {"-SIZE", "-PATH"};
    void run() override;

    explicit Mkdisk(const vector<Param>& parametros);
    int size = 0;
    char f = 'B';
    char u = 'M';
    string  path;
};


#endif //MIA_PROYECTO1_201904061_MKDISK_H
