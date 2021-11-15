//
// Created by jose on 24/08/21.
//

#include <iostream>

#include "Mkfs.h"

using namespace std;

Mkfs::Mkfs(const vector<Param> &parametros):Command(parametros) {
    commandName = "MKFS";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }
}

void Mkfs::run() {
    cout << "Formateo realizado con exito" << endl;
}