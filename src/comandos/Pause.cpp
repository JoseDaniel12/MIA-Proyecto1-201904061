//
// Created by jose on 9/12/21.
//

#include "iostream"

#include "Pause.h"

using namespace std;

Pause::Pause(const vector<Param>& parametros) : Command(parametros) {
    commandName = "PAUSE";
}

void Pause::run() {
    if (!runnable) {
        return;
    }

    cout << "-> Presione una tecla para continuar: ";
    getchar();
}