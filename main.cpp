#include <iostream>
#include <FlexLexer.h>
#include <string>
#include <bits/stdc++.h>
#include "./analizador/scanner.h"
#include "./analizador/parser.h"
#include "Command.h"

using namespace std;

extern int yyparse();
extern Command* resAnalizer;

int main() {
    string entrada;
    while(entrada != "exit") {
        cout << "Ingrese un comando para ejecutar: \n > ";
        getline(cin, entrada);
        char entradaCharArray[entrada.length() + 1];
        strcpy(entradaCharArray, entrada.c_str());
        YY_BUFFER_STATE buffer = yy_scan_string(entradaCharArray);
        if (yyparse() == 0) {
            resAnalizer->run();
        } else {
            cout << "ERROR: Comando no valido" << endl;
        }
        resAnalizer = NULL;
    }
    return 0;
}