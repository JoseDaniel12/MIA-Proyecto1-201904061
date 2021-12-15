//
// Created by jose on 28/11/21.
//

#include <iostream>
#include <fstream>
#include <filesystem>

#include "MkFile.h"

using namespace std;

MkFile::MkFile(vector<Param> parametros) : Command(parametros) {
    commandName = "MKFILE";
    if (!correctParams(parametros, admisableParams, obligatoryParams)) {
        cout << "\nCommando erroneo: " << commandName << endl;
        runnable = false;
        return;
    }

    for (const Param& p: parametros) {
        if (p.name == "-PATH") {
            path = quitarComillas(p.value);
        } else if (p.name == "-P") {
            r = true;
        } else if (p.name == "-SIZE") {
            size = stoi(p.value);
        } else if (p.name == "-CONT") {
            cont = quitarComillas(p.value);
        } else if (p.name == "-STDIN") {
            pStdin = true;
        }
    }
}

void MkFile::run() {
    if (!runnable) {
        return;
    }

    if (!usuario_montado.logeado) {
        cout << "Error: no se puede ejcutar el comando pues no hay nigun usuario logeado" << endl;
        return;
    }

    if (size < 0) {
        cout << "Error: el tamano del archivo no puede ser negativo." << endl;
        return;
    }

    string contenido_archivo = "";
    if (cont != "") {
        if (filesystem::exists(rootPath + cont)) {
            ifstream archivo_con_contenido(rootPath + cont);
            string linea;
            while (getline (archivo_con_contenido, linea)) {
                contenido_archivo += linea += "\n";
            }
            contenido_archivo = contenido_archivo.substr(0, contenido_archivo.length() - 1);
            archivo_con_contenido.close();
        } else  {
            cout << "Error: no se encuentra el conteido del archivo en la ruta indicada." << endl;
            return;
        }
    } else if (pStdin) {
        cout << "Ingrese el contenido del archivo: ";
        cin >> contenido_archivo;
    } else {
        while (contenido_archivo.length() < size) {
            for (int i = 0; i < 9; i++) {
                if (contenido_archivo.length() >= size) {
                    break;
                }
                contenido_archivo += to_string(i);
            }
        }
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

    escribirEnArchivo(indice_inodo_archivo, contenido_archivo, usuario_montado.mountedPartition); // Se escribe en el archivo creado

    cout << "Archivo creado con exito" << endl;
}
