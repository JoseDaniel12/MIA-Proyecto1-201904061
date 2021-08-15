//
// Created by jose on 9/08/21.
//

#include <iostream>
#include <vector>
#include <string>

#include "Rmdisk.h"

using namespace  std;

Rmdisk::Rmdisk(const vector<Param>& parametros):Command(parametros) {
    if (!correctParams(parametros,admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }
    path = rootPath + quitarComillas(parametros[0].value);
}

void Rmdisk::run() {
    if (!runnable) {
        return;
    }

    FILE* file = fopen(path.c_str(), "r");
    if (file) {
        string input;
        cout << "Confrimar eliminacion (y/n): ";
        getline(cin, input);
        if (input == "y" || input == "Y") {
            string comando = "rm \"" + path + "\"";
            system(comando.c_str());
            cout << "Disco eliminado con exito." << endl;
        } else {
            cout << "Eliminacion cancelada." << endl;
        }
        fclose(file);
    } else {
        cout << "Error: No existe el dico en la ruta especificada." << endl;
    }
}