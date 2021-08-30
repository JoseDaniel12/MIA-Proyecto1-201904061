//
// Created by jose on 2/08/21.
//

#ifndef ARCHIVOSP1_COMMAND_H
#define ARCHIVOSP1_COMMAND_H

#include <vector>
#include <string>

#include "Param.h"

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
};

#endif //ARCHIVOSP1_COMMAND_H
