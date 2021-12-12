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

    string res;
    cout << "-> Presione (Y) para continuar: ";
    getline(cin, res);
    cout << endl;
}