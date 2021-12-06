//
// Created by jose on 28/11/21.
//

#include <iostream>
#include "MkFile.h"

using namespace std;

MkFile::MkFile(vector<Param> parametros) : Command(parametros) {
    commandName = "MKFILE";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-PATH") {
            path = quitarComillas(p.value);
        } else if (p.name == "-R") {
            r = true;
        } else if (p.name == "-SIZE") {
            size = stoi(p.value);
        } else if (p.name == "-CONT") {
            cont = quitarComillas(p.value);
        } else if (p.name == "-STDIN") {
            pStdin = quitarComillas(p.value);
        } else if (p.name == "-ID") {
            id = quitarComillas(p.value);
        }
    }
}

void MkFile::run() {
    if (!runnable) {
        return;
    }

    string directorio = getDirectory(path);
    string file_name = getFileName(path) + ".txt";

    MountedPartition mp;
    getMounted(id, &mp);

    int indice_inodo = existePathSimulado(path, mp);
    crearArchivo(1, cont, mp);
    cout << leerArchivo(1, mp) << endl;

    cout << "Archivo creado con exito" << endl;
}
