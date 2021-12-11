#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "./analizador/scanner.h"
#include "comandos/Command.h"
#include "structs.h"

using namespace std;

extern int yyparse();
extern Command* resAnalizer;
Usuario usuario_montado = Usuario();

vector<MountedPartition> mountedPartitions;


int main() {
    string entrada;
    while(entrada != "exit") {
        cout << "Ingrese un comando para ejecutar: \n > ";
        getline(cin, entrada);
        char entradaCharArray[entrada.length() + 1];
        strcpy(entradaCharArray, entrada.c_str());
        YY_BUFFER_STATE buffer = yy_scan_string(entradaCharArray);
        if (yyparse() == 0) {
            int status;
            cout << "_____________________________________" << resAnalizer->commandName << "_____________________________________" << endl;
            resAnalizer->run();
            cout << "__________________________________________________________________________";
            for (int i = 0; i < resAnalizer->commandName.size(); i++) {
                cout << "_";
            }
            cout << "\n";
        } else {
            cout << "ERROR: Comando no valido" << endl;
        }
        resAnalizer = NULL;
    }
    return 0;
}