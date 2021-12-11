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
        }
    }
}

void MkFile::run() {
    if (!runnable) {
        return;
    }

    string folder_path = getDirectory(path);
    folder_path = folder_path.substr(0, folder_path.length() - 1);
    string file_name = getFileName(path)  + "." + getExtension(path);

    if (existePathSimulado(path, usuario_montado.mountedPartition) != -1) {
        string res;
        cout << "El archivo ya existe, desea sobrescribirlo (Y/N): ";
        cin >> res;
        if (toUpper(res) != "Y") {
            return;
        }
    }

    int indice_inodo_foler = existePathSimulado(folder_path, usuario_montado.mountedPartition);
    if (indice_inodo_foler == -1 ) {
        if (r) {
            indice_inodo_foler = crearDirectorioAnidado(folder_path, usuario_montado.mountedPartition);
        } else {
            cout << "Error: no existe la ruta en la que se quiere crear el archivo." << endl;
            return;
        }
    }

    int indice_inodo_archivo = crearArchivo(indice_inodo_foler, file_name, usuario_montado.mountedPartition);
    if (indice_inodo_foler == -1) {
        cout << "Error: no se pudo crear el archivo dentro de la carpeta deseada." << endl;
        return;
    }

    escribirEnArchivo(indice_inodo_archivo, cont, usuario_montado.mountedPartition); // Se escribe en el archivo creado

    cout << "Archivo creado con exito" << endl;
}
