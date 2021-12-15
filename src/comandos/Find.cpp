//
// Created by jose on 14/12/21.
//

#include "Find.h"

Find::Find(const vector<Param> &parametros):Command(parametros) {
    commandName = "FIND";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-PATH") {
            path = quitarComillas(p.value);
        } else if (p.name == "-NAME") {
            name = quitarComillas(p.value);
        }
    }
}

void Find::run() {
    if (!runnable) {
        return;
    }

    string path_simulado_folder = getDirectory(path);
    int indice_inodo_folder = existePathSimulado(path_simulado_folder, usuario_montado.mountedPartition);


}