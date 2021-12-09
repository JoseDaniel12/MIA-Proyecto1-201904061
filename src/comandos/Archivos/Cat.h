//
// Created by jose on 7/12/21.
//

#ifndef MIA_PROYECTO1_201904061_CAT_H
#define MIA_PROYECTO1_201904061_CAT_H

#include "../Command.h"

class Cat : public Command {
public:
    void run() override;

    explicit Cat(const vector<Param> &parametros);
    vector<string> nombres_parametros;
    vector<string> rutas_archivos;
};


#endif //MIA_PROYECTO1_201904061_CAT_H
