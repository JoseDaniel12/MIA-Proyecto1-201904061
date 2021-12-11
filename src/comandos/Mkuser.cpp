//
// Created by jose on 10/12/21.
//

#include "iostream"

#include "Mkuser.h"

using namespace std;

Mkuser::Mkuser(const vector<Param> &parametros):Command(parametros) {
    commandName = "MKUSER";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-USR") {
            usr = quitarComillas(p.value);
        } else if (p.name == "-PWD") {
            pwd = quitarComillas(p.value);
        } else if (p.name == "-GRP") {
            grp = quitarComillas(p.value);
        }
    }
}

void Mkuser::run() {
    if (!runnable) {
        return;
    }

    string contenidoUsers = leerArchivo(1, usuario_montado.mountedPartition);
    contenidoUsers += "\n1, U, " + grp + ", " + usr + ", " + pwd;
    limpiarArchivo(1, usuario_montado.mountedPartition);
    string a = leerArchivo(1, usuario_montado.mountedPartition);
    escribirEnArchivo(1, contenidoUsers, usuario_montado.mountedPartition);

    cout << "Usuario creado con exito" << endl;

}
