//
// Created by jose on 6/08/21.
//

#ifndef MIA_PROYECTO1_201904061_PARAM_H
#define MIA_PROYECTO1_201904061_PARAM_H

#include <string>

using namespace std;

class Param {
public:
    string name;
    string value;
    Param(string _name, string _value);
    bool isValid();
};


#endif //MIA_PROYECTO1_201904061_PARAM_H
