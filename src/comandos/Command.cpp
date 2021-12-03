//
// Created by jose on 2/08/21.
//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "Command.h"
#include "../Entidades/Disco.h"

using namespace std;

Command::Command(vector<Param> params) {
}

void Command::run() {
}

bool Command::hasParams(const vector<Param>& params, const vector<string>& paramNames) {
    bool answer = true;
    for (const string& name : paramNames) {
        bool founded = false;
        for (const Param& p: params) {
            if (p.name == name) {
                founded = true;
            }
        }
        answer = answer && founded;
    }
    return answer;
}

bool Command::missingParams(vector<Param> params, vector<string> obligatoryParams) {
    for (string obliParam : obligatoryParams) {
        bool contained = false;
        for (Param p : params) {
            if (p.name == obliParam) {
                contained = true;
            }
        }
        if (!contained) {
            cout << "ERROR: Faltan parametros obligatorios." << endl;
            return true;
        }
    }
    return false;
}

bool Command::inadmisableParams(vector<Param> params, vector<string> admisableParams)  {
    for (Param p : params) {
        bool contained = false;
        for (string admParam : admisableParams) {
            if (p.name == admParam) {
                contained = true;
            }
        }
        if (!contained) {
            cout << "ERROR: Parametros inadmisibles encontrados." << endl;
            return true;
        }
    }
    return false;
}

bool Command::repeatedParams(vector<Param> params) {
    for (Param p1 : params) {
        int cont  = 0;
        for (Param p2 : params) {
            if (p1.name == p2.name) {
                cont++;
            }
        }
        if (cont > 1) {
            cout << "ERROR: Parametros repetidos encontrados." << endl;
            return true;
        }
    }
    return false;
}

bool Command::correctParams(vector<Param> params, vector<string> admisableParams, vector<string> obligatoryParams) {
    bool c1 = missingParams(params, obligatoryParams);
    bool c2 = inadmisableParams(params, admisableParams);
    bool c3 = repeatedParams(params);
    return !c1 && !c2 && !c3;
}

string Command::getDirectory(string path) {
    string delimiter = "/";
    size_t pos = 0;
    string res = "";
    while((pos = path.find(delimiter)) != string::npos){
        res += path.substr(0, pos) + "/";
        path.erase(0, pos + delimiter.length());
    }
    return res;
}

string Command::getFileName(string path) {
    string delimiter = "/";
    size_t pos = 0;
    string res;
    while((pos = path.find(delimiter))!=string::npos){
        path.erase(0,pos + delimiter.length());
    }
    delimiter = ".";
    pos = path.find(delimiter);
    res = path.substr(0,pos);
    return res;
}

string Command::getExtension(const string& path) {
    string delimiter = ".";
    int pos = (int)path.find(delimiter);
    string res = path.substr(pos + 1,path.size() - 1);
    return res;
}

string Command::quitarComillas(string s) {
    if ((s[0] == '\'' || s[0] == '\"') &&
    (s[s.length()-1] == '\'' || s[s.length()-1] == '\"')) {
        return s.substr(1, s.length()-2);
    }
    return s;
}

int Command::convertToBytes(int bytes, char unit) {
    if (unit == 'B') {
         return bytes;
    } else if (unit == 'K') {
        return bytes * 1024;
    } else if (unit == 'M') {
        return  bytes * 1024 * 1024;
    }
    return -1;
}

string Command::toUpper(const string& cadena) {
    string res;
    for (char i : cadena) {
        res += (char)toupper(i);
    }
    return res;
}

void Command::getMounted(string id, MountedPartition* destinoMp) {
    for (auto mp : mountedPartitions) {
        if (id == mp.id) {
            *destinoMp = mp;
        }
    }
}

vector<string> Command::getPathSeparado(string path) {
    vector<string> res;
    string carpeta_archivo_nombre = "";
    int cont = 0;
    for (auto caracter : path) {
        if (caracter == '/') {
            cont += 1;
            if (cont == 1) {
                continue;
            }
            res.push_back(carpeta_archivo_nombre);
            carpeta_archivo_nombre = "";
        } else {
            carpeta_archivo_nombre += caracter;
        }
    }
    if (carpeta_archivo_nombre != "") {
        res.push_back(carpeta_archivo_nombre);
    }
    return res;
}

Inodo Command::getInodoByIndex(int indice, MountedPartition mp) {
    FILE* file = fopen(mp.path.c_str(), "rb+"); // Se abre el archivo del disco que contiene la particion montada
    fseek(file, mp.partition.part_start, SEEK_SET);   // Se mueve el puntero al area de la particion montada

    // Se recoge el super bloque
    SuperBloque sp;
    fread(&sp, sizeof (SuperBloque), 1, file);

    Inodo inodo;
    fseek(file, sp.s_inode_start, SEEK_SET); // Se mueve el puntero al area de los inodos
    fseek(file, indice * sizeof(Inodo), SEEK_CUR); // Se mueve el puntero al inicio del inodo indicado
    fread(&inodo, sizeof(Inodo), 1, file); // Se recoge el inodo indicado

    fclose(file);
    return inodo;
}

BloqueDePunteros Command::getBloqueDePunteroByIndex(int indice, MountedPartition mp) {
    FILE* file = fopen(mp.path.c_str(), "rb+"); // Se abre el archivo del disco que contiene la particion montada
    fseek(file, mp.partition.part_start, SEEK_SET);   // Se mueve el puntero al area de la particion montada

    // Se recoge el super bloque
    SuperBloque sp;
    fread(&sp, sizeof (SuperBloque), 1, file);

    BloqueDePunteros bloqueDePunteros;
    fseek(file, sp.s_block_start, SEEK_SET); // Se mueve el puntero al area de los bloques
    fseek(file, indice * 64, SEEK_CUR); // Se mueve el puntero al inicio del inodo indicado
    fread(&bloqueDePunteros, sizeof(Inodo), 1, file); // Se recoge el bloque indicado

    fclose(file);
    return bloqueDePunteros;
}


vector<int> Command::getIndicesBloquesCarpetaDeInodo(Inodo inodo, MountedPartition mp) {
    vector<int> apuntadores;
    if (inodo.i_type == 0) { // Si el tipo de inodo es de tipo de carpeta se procede a buscar los apuntadores
        for (int i = 0; i < 15; i++) {
            if (inodo.i_block[i] != -1) {
                if (i < 12) {   // Apuntador Directo a Bloque
                    apuntadores.push_back(inodo.i_block[i]);
                } else if (i == 12) {   // Apuntador Indirecto Simple a Bloque
                    BloqueDePunteros bp1 = getBloqueDePunteroByIndex(inodo.i_block[i], mp);
                    for (int j = 0; j < 16; j++) {
                        if (bp1.b_pointers[j] != -1) {
                            apuntadores.push_back(bp1.b_pointers[j]);
                        }
                    }
                } else if (i == 13) { // Apuntador Indirecto Doble a Bloque
                    BloqueDePunteros bp1 = getBloqueDePunteroByIndex(inodo.i_block[i], mp);
                    for (int j = 0; j < 16; j++) {
                        if (bp1.b_pointers[j] != -1) {
                            BloqueDePunteros bp2 = getBloqueDePunteroByIndex(bp1.b_pointers[j], mp);
                            for (int k = 0; k < 16; k++) {
                                if (bp2.b_pointers[k] != -1) {
                                    apuntadores.push_back(bp2.b_pointers[k]);
                                }
                            }
                        }
                    }
                } else if (i == 14) { // Apuntador Indirecto Triple a Bloque
                    BloqueDePunteros bp1 = getBloqueDePunteroByIndex(inodo.i_block[i], mp);
                    for (int j = 0; j < 16; j++) {
                        if (bp1.b_pointers[j] != -1) {
                            BloqueDePunteros bp2 = getBloqueDePunteroByIndex(bp1.b_pointers[j], mp);
                            for (int k = 0; k < 16; k++) {
                                if (bp2.b_pointers[k] != -1) {
                                    BloqueDePunteros bp3 = getBloqueDePunteroByIndex(bp2.b_pointers[k], mp);
                                    for (int l = 0; l < 16; l++) {
                                        if (bp3.b_pointers[l] != -1) {
                                            apuntadores.push_back(bp3.b_pointers[l]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return apuntadores;
}



int Command::existePathSimulado(string pathSimulado, MountedPartition mp, int indice_inodo) {
    vector<string> path_separado = getPathSeparado(pathSimulado);
    FILE* file = fopen(mp.path.c_str(), "rb+"); // Se abre el archivo del disco que contiene la particion montada
    fseek(file, mp.partition.part_start, SEEK_SET);   // Se mueve el puntero al area de la particion montada

    // Se recoge el super bloque
    SuperBloque sp;
    fread(&sp, sizeof (SuperBloque), 1, file);


    // Se recoge el inodo indicado y se obtiene todos los aputnadores a bloques de carpetas
    // como si todos fuesen directos
    Inodo inodo = getInodoByIndex(indice_inodo, mp);
    vector<int> indices_bloques_carpeta = getIndicesBloquesCarpetaDeInodo(inodo, mp);

    for (auto indice_bloque : indices_bloques_carpeta) {
        BloqueDeCarpeta bloqueDeCarpeta;
        fseek(file, sp.s_block_start, SEEK_SET); // Se mueve el puntero al area de los bloques
        fseek(file, indice_bloque * 64, SEEK_CUR); // Se mueve el puntero al bloque deseado
        fread(&bloqueDeCarpeta, sizeof(BloqueDeCarpeta), 1,file);  // Se lee el bloque deseado

        // Si se pudo leer el bloque se recoren las estructuras "contenido" del bloque de carpeta
        for (int j = 0; j < 4; j++) {
            // Si uno de los ccontenidos tiene como valor el nombre de la carpeta o archivo buscado se elige
            if (bloqueDeCarpeta.b_content[j].b_name == path_separado[0]) {
                // Se crea el path hijo para seguir buscando sin la primera carpeta padre
                vector<string> path_hijo_separado = path_separado;
                path_hijo_separado.erase(path_separado.begin());

                // Si el path queda vacio quiere decir que se llego al final por lo que se retorna
                // el inodo que cotiene la carpeta
                if (path_hijo_separado.size() == 0) {
                    return indice_inodo;
                }

                // De lo contario se unifica el path hijo
                string path_hijo_unido = "/";
                for (auto nombre: path_hijo_separado) {
                    path_hijo_unido += "/" + nombre;
                }

                // y se sique buscando de forma recursiva con el path hijo
                int res_busqueda = existePathSimulado(path_hijo_unido, mp, bloqueDeCarpeta.b_content[j].b_inodo);
                if (res_busqueda != -1) {
                    return res_busqueda;
                }
            }
        }
    }
    return -1;
}

