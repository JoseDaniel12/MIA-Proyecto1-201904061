//
// Created by jose on 7/12/21.
//

#include <iostream>
#include <algorithm>

#include "Cat.h"

using namespace std;

Cat::Cat(const vector<Param> &parametros):Command(parametros) {
    commandName = "CAT";

    for (const Param& p: parametros) {
        nombres_parametros.push_back(p.name);
    }
    sort(nombres_parametros.begin(), nombres_parametros.end());
    for (auto nombre_parametro : nombres_parametros) {
        for (auto p : parametros) {
            if (nombre_parametro == p.name) {
                rutas_archivos.push_back(quitarComillas(p.value));
                break;
            }
        }
    }
}


void Cat::run() {
    for (auto ruta : rutas_archivos) {
        int indice_inodo_archivo = existePathSimulado(ruta, usuario_montado.mountedPartition);
        cout << "______________________________________________" << endl;
        cout << getFileName(ruta) + "." + getExtension(ruta) << ": " << endl;
        cout << leerArchivo(indice_inodo_archivo, usuario_montado.mountedPartition) << endl;
    }
    cout << "______________________________________________" << endl;
}
