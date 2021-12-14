//
// Created by jose on 29/08/21.
//

#ifndef MIA_PROYECTO1_201904061_REP_H
#define MIA_PROYECTO1_201904061_REP_H


#include "Command.h"
#include "../structs.h"

extern vector<MountedPartition> mountedPartitions;

class Rep : public Command {
public:
    vector<string> admisableParams = {"-NAME", "-PATH", "-ID", "-RUTA", "-ROOT"};
    vector<string> obligatoryParams = {"-NAME", "-PATH", "-ID"};
    virtual void run() override;

    Rep(const vector<Param>& params);
    string name;
    string path;
    string id;
    string ruta;
    int root;
    int unique_id;

    string getDotBitmap(MountedPartition mp, bool de_inodos);
    bool crearImgenDeDot(string dot, string ruta_imagen);
    string get_unic_id();
    string getDotInodo(int indice_inodo, MountedPartition mp, string* destino_dot, string id_padre = "-1", bool graficar_apuntadores = false);
    void crearReporteInodos(MountedPartition mp, string ruta);
    void crearReporteBloques(MountedPartition mp, string ruta_reporte);
    string getDotBloqueDeArchivo(int indice_bloque_archivo, MountedPartition mp, string* destino_dot, string id_padre = "-1");
    string getDotBloqueDeCarpeta(int indice_bloque_carpeta, MountedPartition mp, string* destino_dot, string id_padre = "-1", bool graficar_apuntadores = false);
    void crearReporteTree(MountedPartition mp, string ruta_reporte);
    void crearReportSuperBloque(MountedPartition mp, string ruta_reporte);
    void hacerReporteDeArchivo(MountedPartition mp, string ruta_archivo_simulad, string ruta_reporte);
};

#endif //MIA_PROYECTO1_201904061_REP_H
