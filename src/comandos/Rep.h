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

    string ReportTree(MountedPartition _MountedPartition, string _root);
    string getDotTree(int _index_inode, int _start_inodes, int _start_blocks, string _path, int _index_root);
    string getDot_inode_tree(Inodo _inode, int _index_inode);
    string getDot_folder_block_tree(int _start_blocks, int _index_block, string _path);
    string getDot_file_block_tree(int _start_blocks, int _index_block, string _path);


};

#endif //MIA_PROYECTO1_201904061_REP_H
