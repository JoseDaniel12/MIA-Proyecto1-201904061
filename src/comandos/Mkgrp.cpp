//
// Created by jose on 10/12/21.
//

#include "Mkgrp.h"

#include "iostream"

using namespace std;

Mkgrp::Mkgrp(vector<Param> parametros) : Command(parametros) {
    commandName = "MKGRP";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-NAME") {
            name = quitarComillas(p.value);
        }
    }
}


void Mkgrp::run() {
    if (!runnable) {
        return;
    }

    string contenidoUsers = leerArchivo(1, usuario_montado.mountedPartition);
    contenidoUsers += "\n1, G, " + name;
    limpiarArchivo(1, usuario_montado.mountedPartition);
    escribirEnArchivo(1, contenidoUsers, usuario_montado.mountedPartition);

    cout << "Grupo creado con exito" << endl;
}
