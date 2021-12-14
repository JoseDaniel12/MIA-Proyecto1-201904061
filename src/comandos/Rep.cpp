//
// Created by jose on 29/08/21.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>

#include "Rep.h"
#include "../Entidades/Disco.h"


using namespace std;
using std::filesystem::is_directory;

Rep::Rep(const vector<Param>& parametros) : Command(parametros) {
    commandName = "REP";
    unique_id  = 0;
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
            id = quitarComillas(p.value);
        } else if (p.name == "-RUTA") {
            ruta = quitarComillas(p.value);
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
                cout << "Reporte de Disco generado." << endl;
            } else if (name == "MBR") {
                disco.generarReporteMbr(getDirectory(path), getFileName(path), getExtension(path));
                cout << "Reporte de Mbr generado." << endl;
            } else if (name == "BM_INODE") {
                crearImgenDeDot(getDotBitmap(mp, true), path);
                cout << "Reporte de Bitmap de Inodos generado." << endl;
            } else if (name == "BM_BLOCK") {
                crearImgenDeDot(getDotBitmap(mp, false), path);
                cout << "Reporte de Bitmpa de Bloques generado." << endl;
            } else if (name == "INODE") {
                crearReporteInodos(mp, path);
            } else if (name == "BLOCK") {
                crearReporteBloques(mp, path);
            } else if (name == "TREE") {
                crearReporteTree(mp, path);
            } else if (name == "SB") {
                crearReportSuperBloque(mp, path);
            } else if (name == "FILE") {
                hacerReporteDeArchivo(mp, ruta, path);
            }

            else {
                cout << "Error: No existe reporte con el name escogido." << endl;
                return;
            }
            break;
        }
    }
    if (!particionMontada) {
        cout << "Error: No se encontro niguna particion montada con ese ID." << endl;
        return;
    }
}


string Rep::get_unic_id() {
    int res = unique_id;
    unique_id += 1;
    return "i" + to_string(res);
}


bool Rep::crearImgenDeDot(string dot_text, string ruta_imagen) {
    string directory = getDirectory(ruta_imagen);
    string fileName = getFileName(ruta_imagen);
    string extension = getExtension(ruta_imagen);

    if (!is_directory(directory)) {
        string comando = "mkdir -p \'" + directory +"\'";
        system(comando.c_str());
    }

    ofstream file;
    file.open(directory + fileName + ".dot");
    file << dot_text;
    file.close();
    string comando = "dot -T" + extension + " " +  directory + fileName + ".dot -o " + directory + fileName + "." + extension;
    system(comando.c_str());
    string dotPath = directory + fileName + ".dot";
    remove(dotPath.c_str());

}


string Rep::getDotBitmap(MountedPartition mp, bool de_inodos) {
    string dot = "digraph { \n";
    dot += "rankdir = LR \n";
    dot += "node[shape = record] \n";
    dot += "struct [";
    dot += "label = ";
    dot += "\"";
    string bit_map;
    if (de_inodos) {
        dot += "Bitmap de Inodos|";
        bit_map = getBitmap(mp, true);
    } else {
        dot += "Bitmap de Bloques|";
        bit_map = getBitmap(mp, false);
    }
    for (int i = 0; i < bit_map.length() - 1; i++) {
        dot += bit_map.substr(i, 1) + " ";
        if ((i + 1)  % 60 == 0) {
            dot += "\\l";
        }
    }
    if (dot[dot.length() - 1] != 'l') {
        dot += "\\l";
    }
    dot += "\"";
    dot += "] \n";
    dot += "}";
    return dot;
}


string Rep::getDotInodo(int indice_inodo, MountedPartition mp, string* destino_dot, string id_padre, bool graficar_apuntadores) {
    Inodo inodo = getInodoByIndex(indice_inodo, mp);
    string id_inodo = get_unic_id();

    string dot_bloques  = "";
    string dot_text= "//Inodo \n";
    dot_text += id_inodo + " [ \n";
    dot_text += "shape=plaintext \n";
    dot_text += "label=< \n";
    dot_text += "<table> \n";

    dot_text += "<tr> \n";
    dot_text += "<td><b>Inodo No: </b></td> \n";
    dot_text += "<td><b>" + to_string(indice_inodo) + "</b></td> \n";
    dot_text += "</tr> \n";

    // i_uid
    dot_text += "<tr> \n";
    dot_text += "<td>i_uid: </td> \n";
    dot_text += "<td>"+ to_string(inodo.i_uid) + "</td> \n";
    dot_text += "</tr> \n";

    // i_gid
    dot_text += "<tr> \n";
    dot_text += "<td>i_gid: </td> \n";
    dot_text += "<td>"+ to_string(inodo.i_gid) + "</td> \n";
    dot_text += "</tr> \n";

    // i_size
    dot_text += "<tr> \n";
    dot_text += "<td>i_size: </td> \n";
    dot_text += "<td>"+ to_string(inodo.i_size) + "</td> \n";
    dot_text += "</tr> \n";

    // i_atime
    dot_text += "<tr> \n";
    dot_text += "<td>i_atime: </td> \n";
    dot_text += "<td>";
    dot_text += asctime(localtime(&inodo.i_atime));
    dot_text += "</td> \n";
    dot_text += "</tr> \n";

    // i_ctime
    dot_text += "<tr> \n";
    dot_text += "<td>i_ctime: </td> \n";
    dot_text += "<td>";
    dot_text += asctime(localtime(&inodo.i_ctime));
    dot_text += "</td> \n";
    dot_text += "</tr> \n";

    // i_mtime
    dot_text += "<tr> \n";
    dot_text += "<td>i_mtime: </td> \n";
    dot_text += "<td>";
    dot_text += asctime(localtime(&inodo.i_mtime));
    dot_text += "</td> \n";
    dot_text += "</tr> \n";

    // Apuntadores
    for (int i = 0; i < 15; i++) {
        string id_apuntador = id_inodo + "_" + to_string(i);
        dot_text += "<tr> \n";
        dot_text += "<td>i_block_" + to_string(i) + ": </td> \n";
        dot_text += "<td port = \'" + id_apuntador + "\'>"+ to_string(inodo.i_block[i]) + "</td> \n";
        dot_text += "</tr> \n";
        if (graficar_apuntadores && inodo.i_block[i] != -1) {
            if (i < 12) {
                string dot_bloque;
                if (inodo.i_type == '1') {
                    getDotBloqueDeArchivo(inodo.i_block[i], mp, &dot_bloque, id_inodo + ":" + id_apuntador);
                } else {
                    getDotBloqueDeCarpeta(inodo.i_block[i], mp, &dot_bloque, id_inodo + ":" + id_apuntador, true);
                }
                dot_bloques += dot_bloque;
            }
        }
    }

    // i_type
    dot_text += "<tr> \n";
    dot_text += "<td>i_type: </td> \n";
    dot_text += "<td>"+ to_string(inodo.i_type) + "</td> \n";
    dot_text += "</tr> \n";

    // i_perm
    dot_text += "<tr> \n";
    dot_text += "<td>i_perm: </td> \n";
    dot_text += "<td>"+ to_string(inodo.i_perm) + "</td> \n";
    dot_text += "</tr> \n";

    dot_text += "</table> \n";
    dot_text += ">]; \n\n";

    dot_text += dot_bloques;

    if (id_padre != "-1") {
        dot_text += id_padre + " -> " + id_inodo + "\n";
    }

    if (destino_dot != nullptr) {
        *destino_dot = dot_text;
    }
    return id_inodo;
}


string Rep::getDotBloqueDeArchivo(int indice_bloque_archivo, MountedPartition mp, string* destino_dot, string id_padre) {
    BloqueDeArchivo bloqueDeArchivo = getBloqueDeArchivoByIndex(indice_bloque_archivo, mp);
    string id_bloque = get_unic_id();

    string dot_text = "//Bloque de archivo \n";
    dot_text += id_bloque + " [ \n";
    dot_text += "shape=plaintext \n";
    dot_text += "label=< \n";
    dot_text += "<table> \n";

    // Encabezado
    dot_text += "<tr> \n";
    dot_text += "<td><b>(De archivo) Bloque No: </b></td> \n";
    dot_text += "<td><b>" + to_string(indice_bloque_archivo) + "</b></td> \n";
    dot_text += "</tr> \n";

    // b_content
    dot_text += "<tr> \n";
    dot_text += "<td>b_content: </td> \n";
    dot_text += "<td>";
    dot_text += bloqueDeArchivo.b_content;
    dot_text += "</td> \n";
    dot_text += "</tr> \n";

    dot_text += "</table> \n";
    dot_text += ">]; \n\n";

    if (id_padre != "-1") {
        dot_text += id_padre + " -> " + id_bloque + "\n";
    }

    if (destino_dot != nullptr) {
        *destino_dot = dot_text;
    }
    return id_bloque;
}


string Rep::getDotBloqueDeCarpeta(int indice_bloque_carpeta, MountedPartition mp, string* destino_dot, string id_padre, bool graficar_apuntadores) {
    BloqueDeCarpeta bloqueDeCarpeta = getBloqueDeCarpetaByIndex(indice_bloque_carpeta, mp);
    string id_bloque = get_unic_id();

    string dot_inodos = "";
    string dot_text = "//Bloque de carepta \n";
    dot_text += id_bloque + " [ \n";
    dot_text += "shape=plaintext \n";
    dot_text += "label=< \n";
    dot_text += "<table> \n";

    // Encabezado
    dot_text += "<tr> \n";
    dot_text += "<td><b>(De carpeta) Bloque No: </b></td> \n";
    dot_text += "<td><b>" + to_string(indice_bloque_carpeta) + "</b></td> \n";
    dot_text += "</tr> \n";

    // b_content
    for (int i = 0; i < 4; i++) {
        string id_apuntador = id_bloque + "_" + to_string(i);
        dot_text += "<tr> \n";
        dot_text += "<td>";
        dot_text += bloqueDeCarpeta.b_content[i].b_name;
        dot_text += "</td> \n";
        dot_text += "<td port = \'" + id_apuntador + "\'>" + to_string(bloqueDeCarpeta.b_content[i].b_inodo) + "</td> \n";
        dot_text += "</tr> \n";
        string dot_inodo;
        if (graficar_apuntadores) {
            if (i >= 2 && bloqueDeCarpeta.b_content[i].b_inodo != -1) {
                getDotInodo(bloqueDeCarpeta.b_content[i].b_inodo, mp, &dot_inodo, id_bloque + ":" + id_apuntador, true);
            }
        }
        dot_inodos += dot_inodo;
    }

    dot_text += "</table> \n";
    dot_text += ">]; \n\n";

    dot_text += dot_inodos;

    if (id_padre != "-1") {
        dot_text += id_padre + " -> " + id_bloque + "\n";
    }

    if (destino_dot != nullptr) {
        *destino_dot = dot_text;
    }
    return id_bloque;
}


void Rep::crearReporteInodos(MountedPartition mp, string ruta_reporte) {
    string dot_text = "digraph Inodos { \n";
    dot_text += "rankdir = UD \n";

    string bm_inodos = getBitmap(mp, true);
    for (int i = 0; i < bm_inodos.length(); i++) {
        string dot_inodo;
        if (bm_inodos[i] == '1') {
            getDotInodo(i, mp, &dot_inodo);
        }
        dot_text += dot_inodo;
    }

    dot_text += "}";

    crearImgenDeDot(dot_text, ruta_reporte);
    cout << "Reporte de Inodos generado." << endl;
}


void Rep::crearReporteBloques(MountedPartition mp, string ruta_reporte) {
    string dot_text = "digraph Bloques { \n";
    dot_text += "rankdir = UD \n";

    string bm_bloques = getBitmap(mp, false);
    string bm_inodos = getBitmap(mp, true);
    for (int i = 0; i < bm_bloques.length(); i++) {
        string dot_bloque;
        if (bm_bloques[i] == '1') {
            for (int j = 0; j < bm_inodos.length(); j++) {
                if (bm_inodos[j] == '1') {
                    Inodo inodo = getInodoByIndex(j, mp);
                    for (int k = 0; k < 12; k++) {
                        if (inodo.i_block[k] == i) {
                            if (inodo.i_type == '1') {
                                getDotBloqueDeArchivo(i, mp, &dot_bloque);
                            } else {
                                getDotBloqueDeCarpeta(i, mp, &dot_bloque);
                            }
                            goto dot_de_bloque_obtenido;
                        }
                    }
                }
            }
        }
        dot_de_bloque_obtenido:
        dot_text += dot_bloque;
    }

    dot_text += "}";

    crearImgenDeDot(dot_text, ruta_reporte);
    cout << "Reporte de Bloques generado." << endl;
}


void Rep::crearReporteTree(MountedPartition mp, string ruta_reporte) {
    string dot_tree = "digraph Tree { \n";
    dot_tree += "rankdir = LR \n";
    string tree_content;
    getDotInodo(0, mp, &tree_content, "-1", true);
    dot_tree += tree_content;
    dot_tree += "}";
    crearImgenDeDot(dot_tree, ruta_reporte);
    cout << "Reporte de Tree generado." << endl;
}

void Rep::crearReportSuperBloque(MountedPartition mp, string ruta_reporte) {
    string dot_text = "digraph SuperBloque { \n";
    dot_text += "rankdir = LR \n";

    FILE *file = fopen(mp.path.c_str(), "rb+"); // Se abre el archivo del disco que contiene la particion montada
    fseek(file, mp.partition.part_start, SEEK_SET);   // Se mueve el puntero al area de la particion montada

    // Se recoge el super bloque
    SuperBloque sp;
    fread(&sp, sizeof(SuperBloque), 1, file);

    dot_text += "//Bloque de archivo \n";
    dot_text += "sb [ \n";
    dot_text += "shape=plaintext \n";
    dot_text += "label=< \n";
    dot_text += "<table> \n";

    // encabezado
    dot_text += "<tr> \n";
    dot_text += "<td><b>Reporte: </b></td> \n";
    dot_text += "<td><b> Super Bloque </b></td> \n";
    dot_text += "</tr> \n";

    // s_filystem_type
    dot_text += "<tr> \n";
    dot_text += "<td>s_filystem_type: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_filesystem_type) + "</td> \n";
    dot_text += "</tr> \n";

    // s_inodes_count
    dot_text += "<tr> \n";
    dot_text += "<td>s_inodes_count: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_inodes_count) + "</td> \n";
    dot_text += "</tr> \n";

    // s_blocks_count
    dot_text += "<tr> \n";
    dot_text += "<td>s_blocks_count: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_blocks_count) + "</td> \n";
    dot_text += "</tr> \n";

    // s_free_blocks_count
    dot_text += "<tr> \n";
    dot_text += "<td>s_free_blocks_count: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_free_blocks_count) + "</td> \n";
    dot_text += "</tr> \n";

    // s_free_inodes_count
    dot_text += "<tr> \n";
    dot_text += "<td>s_free_inodes_count: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_free_inodes_count) + "</td> \n";
    dot_text += "</tr> \n";

    // s_free_inodes_count
    dot_text += "<tr> \n";
    dot_text += "<td>s_free_inodes_count: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_free_inodes_count) + "</td> \n";
    dot_text += "</tr> \n";

    // s_mtime
    dot_text += "<tr> \n";
    dot_text += "<td>i_atime: </td> \n";
    dot_text += "<td>";
    dot_text += asctime(localtime(&sp.s_mtime));
    dot_text += "</td> \n";
    dot_text += "</tr> \n";

    // s_umtime
    dot_text += "<tr> \n";
    dot_text += "<td>s_umtime: </td> \n";
    dot_text += "<td>";
    dot_text += asctime(localtime(&sp.s_umtime));
    dot_text += "</td> \n";
    dot_text += "</tr> \n";

    // s_mnt_count
    dot_text += "<tr> \n";
    dot_text += "<td>s_mnt_count: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_mnt_count) + "</td> \n";
    dot_text += "</tr> \n";

    // s_magic
    dot_text += "<tr> \n";
    dot_text += "<td>s_magic: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_magic) + "</td> \n";
    dot_text += "</tr> \n";

    // s_inode_size
    dot_text += "<tr> \n";
    dot_text += "<td>s_inode_size: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_inode_size) + "</td> \n";
    dot_text += "</tr> \n";

    // s_block_size
    dot_text += "<tr> \n";
    dot_text += "<td>s_block_size: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_block_size) + "</td> \n";
    dot_text += "</tr> \n";

    // s_first_ino
    dot_text += "<tr> \n";
    dot_text += "<td>s_block_size: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_first_ino) + "</td> \n";
    dot_text += "</tr> \n";

    // s_first_blo
    dot_text += "<tr> \n";
    dot_text += "<td>s_first_blo: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_first_blo) + "</td> \n";
    dot_text += "</tr> \n";

    // s_bm_inode_start
    dot_text += "<tr> \n";
    dot_text += "<td>s_bm_inode_start: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_bm_inode_start) + "</td> \n";
    dot_text += "</tr> \n";

    // s_bm_block_start
    dot_text += "<tr> \n";
    dot_text += "<td>s_bm_block_start: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_bm_block_start) + "</td> \n";
    dot_text += "</tr> \n";

    // s_inode_start
    dot_text += "<tr> \n";
    dot_text += "<td>s_inode_start: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_inode_start) + "</td> \n";
    dot_text += "</tr> \n";


    // s_block_start
    dot_text += "<tr> \n";
    dot_text += "<td>s_block_start: </td> \n";
    dot_text += "<td>"+ to_string(sp.s_block_start) + "</td> \n";
    dot_text += "</tr> \n";

    dot_text += "</table> \n";
    dot_text += ">]; \n\n";
    dot_text += "}";

    crearImgenDeDot(dot_text, ruta_reporte);
    cout << "Reporte de Super Bloque generado." << endl;
}

void Rep::hacerReporteDeArchivo(MountedPartition mp, string ruta_simulada_archivo, string ruta_reporte) {
    int indice_inodo_archivo = existePathSimulado(ruta_simulada_archivo, mp);
    if (indice_inodo_archivo == -1) {
        cout << "Error: No se encontro el archivo en esa ruta." << endl;
        return;
    }
    string contenido_archivo = leerArchivo(indice_inodo_archivo, mp);
    string contenido_con_formato;
    for (int i = 0; i < contenido_archivo.length(); i++) {
        if (contenido_archivo[i] != '\n') {
            contenido_con_formato += contenido_archivo[i];
        } else {
            contenido_con_formato += "\\l";
        }
    }

    string dot = "digraph { \n";
    dot += "rankdir = LR \n";
    dot += "node[shape = record] \n";
    dot += "struct [ \n";
    dot += "label = ";
    dot += "\"";
    string bit_map;
    dot += getFileName(ruta_simulada_archivo) + "|";
    dot += contenido_archivo;

    dot += "\"";
    dot += "] \n";
    dot += "}";

    crearImgenDeDot(dot, ruta_reporte);
    cout << "Reporte de Archivo generado." << endl;
}