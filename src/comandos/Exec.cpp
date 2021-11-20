//
// Created by jose on 29/08/21.
//

#include <filesystem>
#include <iostream>
#include <fstream>

#include "Exec.h"
#include "../analizador/scanner.h"

using namespace std;
using std::filesystem::exists;

Exec::Exec(const vector<Param>& parametros) : Command(parametros) {
    commandName = "EXEC";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        runnable = false;
        return;
    }
    for (const Param& p: parametros) {
        if (p.name == "-PATH") {
            path = rootPath + quitarComillas(p.value);
        }
    }
}


void Exec::run() {
    if (!runnable) {
        return;
    }

    if (!exists(path)) {
        cout << "Error: No existe el archivo con comando para leer." << endl;
        return;
    }

    string texto;
    ifstream archivo(path);
    while(!archivo.eof()) {
        string linea;
        getline(archivo,linea);
        YY_BUFFER_STATE buffer = yy_scan_string(linea.c_str());
        if (yyparse() == 0) {
            cout << "\n//=====================================" << resAnalizer->commandName << "=====================================\\\\" << endl;
            cout << "Comando analizando: " << linea << endl;
            resAnalizer->run();
            cout << "\\\\==========================================================================";
            for (int i = 0; i < resAnalizer->commandName.size(); i++) {
                cout << "=";
            }
            cout << "//\n";
        } else {
            cout << "ERROR: Comando no valido" << endl;
        }
    }
    archivo.close();

    cout << texto << endl;
}