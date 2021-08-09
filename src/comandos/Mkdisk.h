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
    int size;
    char f = 'B';
    char u = 'm';
    string  path;
    void run() override;
    Mkdisk(const vector<Param>& parametros);
};


#endif //MIA_PROYECTO1_201904061_MKDISK_H
