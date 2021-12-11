//
// Created by jose on 2/08/21.
//

#ifndef ARCHIVOSP1_COMMAND_H
#define ARCHIVOSP1_COMMAND_H

#include <vector>
#include <string>

#include "Param.h"
#include "../structs.h"

extern vector<MountedPartition> mountedPartitions;

using  namespace  std;

class Command {
public:
    string rootPath = "/home/jose/Desktop";
    string commandName = "COMMAND";
    bool runnable = true;
    vector<string> admisableParams = {};
    vector<string> obligatoryParams = {};
    Command(vector<Param> params);
    virtual void run();
    static string toUpper(const string& cadena);
    bool missingParams(vector<Param> params, vector<string> obligatoryParams);
    bool inadmisableParams(vector<Param> params,vector<string> admisableParams);
    bool repeatedParams(vector<Param> params);
    bool correctParams(vector<Param> params, vector<string> admisableParams, vector<string> obligatoryParams);
    string getDirectory(string path);
    string getFileName(string path);
    static string getExtension(const string& path);
    string quitarComillas(string s);
    int convertToBytes(int bytes, char unit);
    static bool hasParams(const vector<Param> &params, const vector<string> &paramNames);
    bool getMounted(string id, MountedPartition* destinoMp);

    vector<string> getPathSeparado(string path);
    string getPathUnido(vector<string> path_separado);
    Inodo getNewInodo();
    BloqueDeCarpeta getNewBloqueDeCarpeta();
    Inodo getInodoByIndex(int indice, MountedPartition mp);
    BloqueDePunteros getBloqueDePunteroByIndex(int indice, MountedPartition mp);
    BloqueDeCarpeta getBloqueDeCarpetaByIndex(int indice_bloque, MountedPartition mp);
    vector<int> getIndicesBloquesCarpetaDeInodo(Inodo inodo, MountedPartition mp);
    int existePathSimulado(string pathSimulado, MountedPartition mp, int indice_inodo = 0);
    string getBitmap(MountedPartition mp, bool de_inodos = true);
    void escribirBitMap(string bit_map, MountedPartition mp, bool de_inodos);
    int getIndiceForNewInodo(MountedPartition mp);
    int getIndiceForNewBloque(MountedPartition mp);
    void escribirBloqueDeArchivo(BloqueDeArchivo bloque, int indice_bloque, MountedPartition mp);
    void escribirBloqueDeCarpeta(BloqueDeCarpeta bloque, int indice_bloque, MountedPartition mp);
    void escribirInodo(Inodo inodo, int indice_inodo, MountedPartition mp);
    int crearArchivo(int indice_inodo, string nombre_archivo, MountedPartition mp);
    int crearCarpeta(int indice_inodo_carpeta_padre, string nombre_carpeta, MountedPartition mp);
    string leerArchivo(int indice_inodo, MountedPartition mp);
    void escribirEnArchivo(int indice_inodo_archivo, string texto, MountedPartition mp);
    void limpiarArchivo(int indice_inodo_archivo, MountedPartition mp);
    vector<vector<string>> getRegistrosArchivoUsuarios(string contenido_archivo_usuarios);
    int crearDirectorioAnidado(string direcorio_anidado, MountedPartition mp);
};

#endif //ARCHIVOSP1_COMMAND_H
