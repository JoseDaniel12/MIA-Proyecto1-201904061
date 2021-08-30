//
// Created by jose on 2/08/21.
//
#include <iostream>
#include "Command.h"

#include <vector>
#include <algorithm>

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
    return c1 == false and c2 == false and c3 == false;
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