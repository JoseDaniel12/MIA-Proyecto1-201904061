//
// Created by jose on 29/08/21.
//

#ifndef MIA_PROYECTO1_201904061_EXEC_H
#define MIA_PROYECTO1_201904061_EXEC_H


#include "Command.h"

extern int yyparse();
extern Command* resAnalizer;

class Exec : public Command {
public:
    vector<string> admisableParams = {"-PATH"};
    vector<string> obligatoryParams = {"-PATH"};
    virtual void run() override;

    explicit Exec(const vector<Param>& params);
    string path;
};


#endif //MIA_PROYECTO1_201904061_EXEC_H
