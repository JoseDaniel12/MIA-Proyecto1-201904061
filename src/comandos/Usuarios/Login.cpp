//
// Created by jose on 24/11/21.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#include "Login.h"

using namespace std;

Login::Login(vector<Param> parametros) : Command(parametros) {
    commandName = "LOGIN";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-USR") {
            user = quitarComillas(p.value);
        } else if (p.name == "-PWD") {
            pwd = quitarComillas(p.value);
        } else if (p.name == "-ID") {
            id = quitarComillas(p.value);
        }
    }
}

void Login::run() {
    if (!runnable) {
        return;
    }

    if (usuario_montado.logeado) {
        cout << "Error: Debe cerrar la sesion activa para logearse." << endl;
        return;
    }

    MountedPartition mountedPartition;
    int existe_mounted = getMounted(id, &mountedPartition);

    if (!existe_mounted) {
        cout << "Error: No se encontro particion montada con ese id." << endl;
    }

    string contenidoUsers = leerArchivo(1, mountedPartition);
    vector<vector<string>> registros = getRegistrosArchivoUsuarios(contenidoUsers);

    for (auto registro : registros) {
        if (registro[0] == "1" && registro[1] == "U" && registro[3] == user && registro[4] == pwd) {
            usuario_montado.nombre = user;
            usuario_montado.contrasena = pwd;
            usuario_montado.grupo = registro[2];
            usuario_montado.mountedPartition = mountedPartition;
            usuario_montado.logeado = true;
        }
    }

    if (!usuario_montado.logeado) {
        cout << "Error: los datos de usuario son errones, no se pudo iniciar sesion." << endl;
        return;
    }

    cout << "Se ha inidciado seccion con exito" << endl;
}

