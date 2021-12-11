//
// Created by jose on 11/12/21.
//

#include "Logout.h"
#include "iostream"

using namespace std;

Logout::Logout(vector<Param> parametros) : Command(parametros) {
    commandName = "LOGOUT";
}

void Logout::run() {
    if (!runnable) {
        return;
    }

    if (!usuario_montado.logeado) {
        cout << "No se encuentra nigun usuario logeado para salir de la sesion." << endl;
        return;
    }

    usuario_montado.logeado = false;
    cout << "Sesion terminada con exito." << endl;
}

