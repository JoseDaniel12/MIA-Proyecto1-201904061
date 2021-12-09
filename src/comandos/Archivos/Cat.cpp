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
    MountedPartition mp;
    getMounted("611a", &mp);

    for (auto ruta : rutas_archivos) {
        int indice_inodo_archivo = existePathSimulado(ruta, mp);
        cout << "______________________________________________" << endl;
        cout << getFileName(ruta) + "." + getExtension(ruta) << ": " << endl;
        cout << leerArchivo(indice_inodo_archivo, mp) << endl;
    }
    cout << "______________________________________________" << endl;
}
