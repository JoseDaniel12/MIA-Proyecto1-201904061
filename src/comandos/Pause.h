//
// Created by jose on 9/12/21.
//

#ifndef MIA_PROYECTO1_201904061_PAUSE_H
#define MIA_PROYECTO1_201904061_PAUSE_H

#include "Command.h"

class Pause : public Command {
public:
    virtual void run() override;

    explicit Pause(const vector<Param>& params);
};


#endif //MIA_PROYECTO1_201904061_PAUSE_H
