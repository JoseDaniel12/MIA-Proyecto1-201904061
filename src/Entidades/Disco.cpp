//
// Created by jose on 23/08/21.
//

#include <utility>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>

#include "Disco.h"
using namespace std;

Disco::Disco(string pathDisco) {
    path = std::move(pathDisco);
}

bool Disco::existeDisco() const {
    FILE* file = fopen(path.c_str(), "rb+");
    if (file == nullptr) {
        return false;
    }
    fclose(file);
    return true;
}

bool Disco::getMBR(MBR* destino) const {
    FILE* file = fopen(path.c_str(), "rb+");
    if (file != nullptr) {
        MBR mbr;
        fseek(file,0,SEEK_SET);
        fread(&mbr, sizeof(MBR), 1, file);
        *destino = mbr;
        return true;
    }
    return false;
}


vector<Partition> Disco::getNonLogialPartitions() const {
    vector<Partition> partitions;
    MBR mbr;
    if (getMBR(&mbr)) {
        for (auto & p : mbr.mbr_partition) {
            if (p.part_status == '1') {
                partitions.push_back(p);
            }
        }
    }
    return partitions;
}

vector<Partition> Disco::getPrimaryPartitions() const {
    vector<Partition> partitions;
    MBR mbr;
    if (getMBR(&mbr)) {
        for (auto & p : mbr.mbr_partition) {
            if (p.part_type == 'P') {
                partitions.push_back(p);
            }
        }
    }
    return partitions;
}

bool Disco::getExtendedPartition(Partition* destino) const {
    vector<Partition> partitions = getNonLogialPartitions();
    for (auto &p: partitions) {
        if (p.part_type == 'E' && p.part_status == '1') {
            *destino = p;
            return true;
        }
    }
    return false;
}

vector<EBR> Disco::getEbrs() const { // AQI HAY ERROR
    FILE* file = fopen(path.c_str(), "rb+");
    vector<EBR> ebrs;

    Partition extendedPartition;
    bool extendidaEncontrada = getExtendedPartition(&extendedPartition);
    if (!extendidaEncontrada) {
        return ebrs;
    }

    EBR ebr;
    fseek(file, extendedPartition.part_start, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, file);
    ebrs.push_back(ebr);

    while (ebr.part_next != -1) {
        EBR nextEbr;
        fseek(file, ebr.part_next, SEEK_SET);
        fread(&nextEbr, sizeof(EBR), 1, file);
        ebrs.push_back(nextEbr);
        ebr = nextEbr;
    }
    return ebrs;
}

vector<Partition> Disco::getLogicalPartitions() const {
    vector<Partition> partitions;
    vector<EBR> ebrs = getEbrs();
    for (auto & e : ebrs) {
        if (e.part_status == '1') {
            Partition p;
            p.part_status = e.part_status;
            p.part_type = 'L';
            p.part_fit = e.part_fit;
            p.part_start = e.part_start;
            p.part_size = e.part_size;
            strcpy(p.part_name, e.part_name);
            partitions.push_back(p);
        }
    }
    return partitions;
}

bool Disco::getPartitionByName(Partition* destino, const string& nombre) const {
    vector<Partition> nonLogicalPartitions = getNonLogialPartitions();
    vector<Partition> logicalPartitions = getLogicalPartitions();
    vector<Partition> partitions;
    partitions.insert(partitions.end(), nonLogicalPartitions.begin(), nonLogicalPartitions.end());
    partitions.insert(partitions.end(), logicalPartitions.begin(), logicalPartitions.end());
    for (auto & p : partitions) {
        if (p.part_name == nombre) {
            *destino = p;
            return true;
        }
    }
    return false;
}

vector<PartitionHole> Disco::getLogicalHoles() const {
    vector<PartitionHole> holes;
    Partition extendedPartition;
    if (!getExtendedPartition(&extendedPartition)) {
        return holes;
    }
    int startPartition = extendedPartition.part_start;
    int endPartition = extendedPartition.part_start + extendedPartition.part_size;
    vector<EBR> ebrs = getEbrs();
    if (ebrs.empty()) {
        return holes;
    } else if (ebrs.size() == 1 && ebrs[0].part_status == '0') {
        PartitionHole hole;
        hole.start =  startPartition;
        hole.size = endPartition;
        holes.push_back(hole);
        return holes;
    }
    for (int i = 0; i < ebrs.size(); i++) {
        if (ebrs[i].part_next != -1 && (ebrs[i].part_start + ebrs[i].part_size) != ebrs[i].part_next) {
            PartitionHole hole;
            hole.start = ebrs[i].part_start + ebrs[i].part_size;
            hole.size = ebrs[i].part_next - hole.start;
            holes.push_back(hole);
        }

        if (i == 0 && ebrs.size() > 1 && ebrs[0].part_status == '0' && ebrs[0].part_next != -1) {
            PartitionHole hole;
            hole.start = startPartition;
            hole.size = ebrs[0].part_next - hole.start;
            holes.push_back(hole);
        } else if (i == ebrs.size() - 1 && ebrs[i].part_start + ebrs[i].part_size != endPartition) {
            PartitionHole hole;
            hole.start = ebrs[i].part_start + ebrs[i].part_size;
            hole.size = endPartition - hole.start;
            holes.push_back(hole);
        }
    }
    return holes;
}

vector<PartitionHole> Disco::getNotLogicalHoles() const {
    MBR mbr;
    getMBR(&mbr);
    int start = sizeof(MBR);
    int end = mbr.mbr_tamano;

    vector<PartitionHole> holes;
    int numActivePartitions = 0;
    for (auto & partition : mbr.mbr_partition) {
        if (partition.part_status == '1') {
            numActivePartitions++;
        }
    }

    if (numActivePartitions == 0) {
        PartitionHole hole;
        hole.start = sizeof(MBR);
        hole.size = mbr.mbr_tamano - hole.start;
        holes.push_back(hole);
        return holes;
    }

    int revisado = 0;
    for (int i = 0; i < 4; i++) {
        if (mbr.mbr_partition[i].part_status == '1') {
            revisado++;
            int nextIndex = i + 1;
            while (mbr.mbr_partition[nextIndex].part_status != '1' && nextIndex < 4) {
                nextIndex++;
            }
            if (nextIndex < 4 && mbr.mbr_partition[nextIndex].part_start - (mbr.mbr_partition[i].part_start + mbr.mbr_partition[i].part_size) != 0) {
                PartitionHole hole;
                hole.start = mbr.mbr_partition[i].part_start + mbr.mbr_partition[i].part_size;
                hole.size = mbr.mbr_partition[nextIndex].part_start - hole.start;
                holes.push_back(hole);
            }
            if (revisado == 1 && mbr.mbr_partition[revisado - 1].part_start != start) {
                PartitionHole hole;
                hole.start = start;
                hole.size = mbr.mbr_partition[revisado - 1].part_start - start;
                holes.push_back(hole);
            } else if (revisado == numActivePartitions && mbr.mbr_partition[revisado - 1].part_start + mbr.mbr_partition[revisado - 1].part_size != end) {
                PartitionHole hole;
                hole.start = mbr.mbr_partition[revisado - 1].part_start + mbr.mbr_partition[revisado - 1].part_size;
                hole.size = end - hole.start;
                holes.push_back(hole);
            }
        }
    }
    return holes;
}



void Disco::generarReporteDisco(const string &directory, const string &fileName, const string &extension) const  {
    vector<PartitionHole> nonLogicalHoles = getNotLogicalHoles();
    vector<PartitionHole> logicalHoles = getLogicalHoles();

    string dotText = "digraph disco { \n";
    dotText += "contenido [shape=none, margin=0, label=< \n";
    dotText += "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\"> \n";
    dotText += "<TR> \n";
    MBR mbr;
    getMBR(&mbr);
    dotText += "<TD ROWSPAN=\"2\"> \n";
    dotText += "_MBR_ \n";
    dotText += "<BR/> Inicio: 0 \n" ;
    dotText += "<BR/> Fin: " + to_string(sizeof(MBR)) + "\n";
    dotText += "</TD> \n\n";

    vector<Partition> nonLogicalPartitions = getNonLogialPartitions();
    for (auto & p : nonLogicalPartitions) {
        if (p.part_type == 'P') {
            for (int i = 0; i < nonLogicalHoles.size(); i++) {
                if (p.part_start > nonLogicalHoles[i].start) {
                    dotText += "<TD ROWSPAN=\"2\"> \n";
                    dotText += "_LIBRE_ \n";
                    dotText += "<BR/> Inicio: " +  to_string(nonLogicalHoles[i].start) + "\n";
                    dotText += "<BR/> Fin: " + to_string(nonLogicalHoles[i].start + nonLogicalHoles[i].size) + "\n";
                    dotText += "<BR/> Porcentaje: " +  truncar((float)p.part_size / (float)mbr.mbr_tamano * 100) + "\n";
                    dotText += "</TD> \n\n";
                    nonLogicalHoles.erase(nonLogicalHoles.begin() +  i);
                    break;
                }
            }
            dotText += "<TD ROWSPAN=\"2\"> \n";
            dotText += "_PRIMARIA_ \n";
            string nombre;
            nombre.append(p.part_name);
            dotText += "<BR/> Nombre: " +  nombre + "\n";
            dotText += "<BR/> Inicio: " + to_string(p.part_start) + "\n";
            dotText += "<BR/> Fin: " + to_string(p.part_start + p.part_size) + "\n";
            dotText += "<BR/> Porcentaje: " + truncar(((float)p.part_size / (float)mbr.mbr_tamano) * 100) + "\n";
            dotText += "</TD> \n\n";
        } else if (p.part_type == 'E') {
            vector<EBR> ebrs = getEbrs();
            dotText += "<TD COLSPAN=\"" + to_string(4*ebrs.size()) +"\"> \n";
            string nombre;
            nombre.append(p.part_name);
            dotText += "_EXTENDIDA_" + nombre +"_\n";
            dotText += "</TD> \n\n";
        }
    }
    for (auto & nonLogicalHole : nonLogicalHoles) {
        dotText += "<TD ROWSPAN=\"2\"> \n";
        dotText += "_LIBRE_ \n";
        dotText += "<BR/> Inicio: " +  to_string(nonLogicalHole.start) + "\n";
        dotText += "<BR/> Fin: " + to_string(nonLogicalHole.start + nonLogicalHole.size) + "\n";
        dotText += "<BR/> Porcentaje: " +  truncar((float)nonLogicalHole.size / (float)mbr.mbr_tamano * 100)  + "\n";
        dotText += "</TD> \n\n";
    }
    dotText += "</TR> \n\n\n";


    Partition extendedParition;
    bool hayExtendida = getExtendedPartition(&extendedParition);
    if (hayExtendida) {
        dotText += "<TR> \n";
        vector<EBR> ebrs = getEbrs();
        for (auto & e : ebrs) {
            for (int i = 0; i < logicalHoles.size(); i++) {
                if (e.part_start > logicalHoles[i].start) {
                    dotText += "<TD> \n";
                    dotText += "_LIBRE_ \n";
                    dotText += "<BR/> Inicio: " +  to_string(logicalHoles[i].start) + "\n";
                    dotText += "<BR/> Fin: " + to_string(logicalHoles[i].start + logicalHoles[i].size) + "\n";
                    dotText += "<BR/> Porcentaje: " +  truncar((float)e.part_size / (float)mbr.mbr_tamano * 100)  + "\n";
                    dotText += "</TD> \n\n";
                    logicalHoles.erase(logicalHoles.begin() +  i);
                    break;
                }
            }
            dotText += "<TD> \n";
            dotText += "_EBR_ \n";
            dotText += "<BR/> Inicio: " + to_string(e.part_start) + "\n";
            dotText += "<BR/> Fin: " + to_string((e.part_start + (int)sizeof(EBR))) + "\n";
            dotText += "</TD> \n\n";

            dotText += "<TD> \n";
            dotText += "_LOGICA_ \n";
            string nombre;
            nombre.append(e.part_name);
            dotText += "<BR/> Nombre: " +  nombre + "\n";
            dotText += "<BR/> Inicio: " + to_string((e.part_start + (int)sizeof(EBR))) + "\n";
            dotText += "<BR/> Fin: " + to_string(e.part_start + e.part_size) + "\n";
            dotText += "<BR/> Porcentaje: " + truncar((float)e.part_size / (float)mbr.mbr_tamano * 100) + "\n";
            dotText += "</TD> \n\n";
        }
        for (auto & logicalHole : logicalHoles) {
            dotText += "<TD> \n";
            dotText += "_LIBRE_ \n";
            dotText += "<BR/> Inicio: " +  to_string(logicalHole.start) + "\n";
            dotText += "<BR/> Fin: " + to_string(logicalHole.start + logicalHole.size) + "\n";
            dotText += "<BR/> Porcentaje: " +  truncar((float)logicalHole.size / (float)mbr.mbr_tamano * 100) + "\n";
            dotText += "</TD> \n\n";
        }
        dotText += "</TR> \n";
    }


    dotText += "</TABLE>>] \n";
    dotText += "}";

    ofstream file;
    file.open(directory + fileName + ".dot");
    file << dotText;
    file.close();
    string comando = "dot -T" + extension + " " +  directory + fileName + ".dot -o " + directory + fileName + "." + extension;
    system(comando.c_str());
    string dotPath = directory + fileName + ".dot";
    remove(dotPath.c_str());
}

string Disco::truncar(float numero) {
    char str[40];
    sprintf(str, "%.2f", numero);

    return str;
}


void Disco::generarReporteMbr(const string& directory, const string& fileName, const string& extension) const {
    string dotText = "digraph mbr { \n";
    dotText += "rankdir=UD \n";
    dotText += "node[shape=box] \n";
    dotText += "concentrate=true \n";

    //MBR
    MBR mbr;
    getMBR(&mbr);
    dotText += "nodo0 [shape=plaintext label=<<table border=\"1\" cellspacing=\"0\"> \n";
    dotText += "<tr><td>Nombre</td> <td>Valor</td></tr> \n";
    dotText += "<tr><td>mbr_tamaño</td> <td>" + to_string(mbr.mbr_tamano) + "</td></tr>\n";
    dotText += "<tr><td>mbr_fecha_creacion</td> <td>" + to_string(mbr.mbr_fecha_creacion) + "</td></tr>\n";
    dotText += "<tr><td>mbr_disk_signature</td> <td>" + to_string(mbr.mbr_disk_signature) + "</td></tr>\n";
    dotText += "<tr><td>Disk_fit</td> <td>" ;
    dotText.push_back(mbr.disk_fit);
    dotText += "</td></tr>\n";
    for (int i = 0; i < 4; i++) {
        Partition p = mbr.mbr_partition[i];
        if (p.part_status == '1') {
            dotText += "<tr><td>part_status_" + to_string(i) + "</td> <td>" + p.part_status + "</td></tr>\n";
            dotText += "<tr><td>part_type_" + to_string(i) + "</td> <td>" + p.part_type + "</td></tr>\n";
            dotText += "<tr><td>part_fit_" + to_string(i) + "</td> <td>" + p.part_fit + "</td></tr>\n";
            dotText += "<tr><td>part_stax_" + to_string(i) + "</td> <td>" + to_string(p.part_start) + "</td></tr>\n";
            dotText += "<tr><td>part_siz_" + to_string(i) + "</td> <td>" + to_string(p.part_size) + "</td></tr>\n";
            dotText += "<tr><td>part_name_" + to_string(i) + "</td> <td>" + p.part_name + "</td></tr>\n";
        }
    }
    dotText += "</table>>] \n\n";

    vector<EBR> ebrs = getEbrs();
    int contador = 1;
    for (auto & e : ebrs) {
        dotText += "nodo" + to_string(contador) + "[shape=plaintext label=<<table border=\"1\" cellspacing=\"0\"> \n";
        dotText += "<tr><td>EBR</td> <td>" + to_string(contador) +"</td></tr> \n";
        dotText += "<tr><td>Nombre</td> <td>Valor</td></tr> \n";
        dotText += "<tr><td>part_status_" + to_string(contador) + "</td> <td>" + e.part_status + "</td></tr>\n";
        dotText += "<tr><td>part_fit_" + to_string(contador) + "</td> <td>" + e.part_fit + "</td></tr>\n";
        dotText += "<tr><td>part_start_" + to_string(contador) + "</td> <td>" + to_string(e.part_start) + "</td></tr>\n";
        dotText += "<tr><td>part_sizq_" + to_string(contador) + "</td> <td>" + to_string(e.part_size) + "</td></tr>\n";
        dotText += "<tr><td>part_next_" + to_string(contador) + "</td> <td>" + to_string(e.part_next) + "</td></tr>\n";
        dotText += "<tr><td>part_name_" + to_string(contador) + "</td> <td>" + e.part_name + "</td></tr>\n";
        dotText += "</table>>] \n\n";
        contador++;
    }

    dotText += "}";

    ofstream file;
    file.open(directory + fileName + ".dot");
    file << dotText;
    file.close();
    string comando = "dot -T" + extension + " " +  directory + fileName + ".dot -o " + directory + fileName + "." + extension;
    system(comando.c_str());
    string dotPath = directory + fileName + ".dot";
    remove(dotPath.c_str());
}


