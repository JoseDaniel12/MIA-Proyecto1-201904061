//
// Created by jose on 29/11/21.
//

#include "iostream"

#include "Mkdir.h"

using namespace std;

Mkdir::Mkdir(const vector<Param> &parametros):Command(parametros) {
    commandName = "MKDIR";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-PATH") {
            path = quitarComillas(p.value);
        } else if (p.name == "-P" and p.value == "-P") {
            param_p = true;
        }
    }
}

void Mkdir::run() {
    if (!runnable) {
        return;
    }

    vector<string> path_separado = getPathSeparado(path);
    string nombre_carpeta_nueva = path_separado[path_separado.size() - 1];
    path_separado.pop_back();
    string path_carpeta_padre = getPathUnido(path_separado);

    if (!usuario_montado.logeado) {
        cout << "Error: no se puede ejcutar el comando pues no hay nigun usuario logeado" << endl;
    }

    int indice_inodo_carpeta_padre = existePathSimulado(path_carpeta_padre, usuario_montado.mountedPartition);
    if (indice_inodo_carpeta_padre == -1) {
        if (param_p) {
            indice_inodo_carpeta_padre = crearDirectorioAnidado(path_carpeta_padre, usuario_montado.mountedPartition);
        } else {
            cout << "Error: no existe la ruta en la que se quiere crear la carpeta." << endl;
            return;
        }
    }

    crearCarpeta(indice_inodo_carpeta_padre, nombre_carpeta_nueva, usuario_montado.mountedPartition);

    cout << "Carpeta creada con exito" << endl;
}