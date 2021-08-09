//
// Created by jose on 2/08/21.
//
#include <iostream>
#include "Command.h"

#include <vector>
#include <algorithm>

using namespace std;

Command::Command(vector<Param> params) {
}

void Command::run() {
}


bool Command::findRepeatedParams(vector<Param> params) {
    return false;
}

bool Command::inadmisableParams(vector<Param> params, vector<string> admisableParams)  {
    for (Param p: params) {
        bool contained = false;
        for (string admParam : admisableParams) {
            if (p.name == admParam) {
                contained = true;
            }
        }
        if (!contained) {
            cout << "Parametros inadmisibles encontrados." << endl;
            return true;
        }

    }
    return false;
}