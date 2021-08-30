//
// Created by jose on 29/08/21.
//

#include <iostream>
#include <filesystem>

#include "Rep.h"
#include "../Entidades/Disco.h"

using namespace std;
using std::filesystem::is_directory;

Rep::Rep(const vector<Param>& parametros) : Command(parametros) {
    commandName = "REP";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-NAME") {
            name = toUpper(p.value);
        } else if (p.name == "-PATH") {
            path = rootPath + quitarComillas(p.value);
        } else if (p.name == "-ID") {
            id = p.value;
        } else if (p.name == "-RUTA") {
            ruta = rootPath + quitarComillas(p.value);
        } else if (p.name == "-ROOT") {
            root  = stoi(p.value);
        }
    }
}

void Rep::run() {
    if (!runnable) {
        return;
    }

    bool particionMontada = false;
    for (auto & mp : mountedPartitions) {
        if (mp.id == id) {
            particionMontada = true;
            Disco disco = Disco(mp.path);
            if (!disco.existeDisco()) {
                cout << "Error: Ya no existe el disco con el path de la particion monatada." << endl;
                return;
            }


            string dir = getDirectory(path);
            if (!is_directory(dir)) {
                string comando = "mkdir -p \'" + dir +"\'";
                system(comando.c_str());
            }

            if (name == "DISK") {
                disco.generarReporteDisco(getDirectory(path), getFileName(path), getExtension(path));
                cout << "Reporte generado." << endl;
            } else if (name == "MBR") {
                disco.generarReporteMbr(getDirectory(path), getFileName(path), getExtension(path));
                cout << "Reporte generado." << endl;
            } else {
                cout << "Error: No existe reporte con el name escogido." << endl;
                return;
            }
        }
    }
    if (!particionMontada) {
        cout << "Error: No se encontro niguna particion montada con ese ID." << endl;
        return;
    }

}