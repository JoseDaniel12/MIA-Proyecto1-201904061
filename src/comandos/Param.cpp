//
// Created by jose on 6/08/21.
//

#include "Param.h"

Param::Param(string _name, string _value) {
    name = _name;
    value = _value;
}

bool Param::isValid() {
    if (name == "mkdsik") {
        return true;
    }
    return false;
}