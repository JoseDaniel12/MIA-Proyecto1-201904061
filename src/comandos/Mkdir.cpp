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
        } else if (p.name == "-P") {
            param_p = quitarComillas(p.value);
        }
    }
}

void Mkdir::run() {
    if (!runnable) {
        return;
    }

    MountedPartition mp;
    getMounted("611a", &mp);

    vector<string> path_separado = getPathSeparado(path);
    string nombre_carpeta_nueva = path_separado[path_separado.size() - 1];
    path_separado.pop_back();
    string path_carpeta_padre = getPathUnido(path_separado);

    int indice_inodo_carpeta_padre = existePathSimulado(path_carpeta_padre, mp);
    crearCarpeta(indice_inodo_carpeta_padre, nombre_carpeta_nueva, mp);

    cout << "Carpeta creada con exito" << endl;
}