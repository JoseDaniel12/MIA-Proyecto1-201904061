//
// Created by jose on 9/12/21.
//

#include <iostream>
#include <fstream>
#include <string.h>

#include "../../structs.h"

using std::string;

string getDotTree(int _index_inode, int _start_inodes, int _start_blocks, string _path, int _index_root);
string getDot_inode_tree(Inodo _inode, int _index_inode);
string getDot_folder_block_tree(int _start_blocks, int _index_block, string _path);
string getDot_file_block_tree(int _start_blocks, int _index_block, string _path);

string ReportTree(MountedPartition _MountedPartition, string _root) /* Este reporte quedó bien mamalon xd */
{
    string grafo =
            std::string("digraph G {\n") +
            +"graph[bgcolor=\"#154a7e\" margin=0]\n" +
            +"rankdir=\"LR\";\n" +
            +"node [shape=plaintext fontname= \"Ubuntu\"];\n" +
            +"edge [arrowhead=\"normal\" penwidth=3];\n\n";

    FILE *file = fopen(_MountedPartition.path.c_str(), "rb");
    /* Lectura del superbloque */
    SuperBloque super_bloque;
    fseek(file, _MountedPartition.partition.part_start, SEEK_SET);
    fread(&super_bloque, sizeof(SuperBloque), 1, file);
    fclose(file);
    file = NULL;

    int index_root = (_root == "") ? (-1) : (std::stoi(_root));
    grafo += getDotTree(0, super_bloque.s_inode_start, super_bloque.s_block_start, _MountedPartition.path, index_root);
    grafo += "\n}";

    return grafo;
}

string getDotTree(int _index_inode, int _start_inodes, int _start_blocks, string _path, int _index_root)
{
    FILE *_file = fopen(_path.c_str(), "rb");
    string _dot = "";
    if (_index_inode == _index_root)
        _index_root = -1;
    /* Leer el inodo */
    Inodo inode_current;
    fseek(_file, _start_inodes, SEEK_SET);
    fseek(_file, _index_inode * sizeof(Inodo), SEEK_CUR);
    fread(&inode_current, sizeof(Inodo), 1, _file);
    fclose(_file);
    if (_index_root == -1)
        _dot += getDot_inode_tree(inode_current, _index_inode);
    if (inode_current.i_type == '0')
    {
        BloqueDeCarpeta folder_block;
        for (int i = 0; i < 15; i++) // falta indirectos
        {
            if (inode_current.i_block[i] != -1)
            { /* Leer el bloque y redireccionar al inodo y ver si de nuevo es otra carpeta */
                if (_index_root == -1)
                    _dot += getDot_folder_block_tree(_start_blocks, inode_current.i_block[i], _path);
                _file = fopen(_path.c_str(), "rb");
                fseek(_file, _start_blocks, SEEK_SET);
                fseek(_file, inode_current.i_block[i] * 64, SEEK_CUR);
                fread(&folder_block, 64, 1, _file);
                fclose(_file);
                for (int j = 0; j < 4; j++)
                {
                    if (folder_block.b_content[j].b_inodo > 0 && folder_block.b_content[j].b_inodo != _index_inode && string(folder_block.b_content[j].b_name) != ".." && string(folder_block.b_content[j].b_name) != ".")
                    {
                        // std::cout << folder_block.b_content[j].b_name << std::endl;
                        _index_inode = folder_block.b_content[j].b_inodo;
                        _dot += getDotTree(_index_inode, _start_inodes, _start_blocks, _path, _index_root);
                    }
                }
            }
        }
    }
    else if (_index_root == -1) // Es inodo de archivo
    {
        for (int i = 0; i < 15; i++)
        {
            if (inode_current.i_block[i] != -1)
                _dot += getDot_file_block_tree(_start_blocks, inode_current.i_block[i], _path);
        }
    }
    // fclose(_file);
    _file = NULL;
    return _dot;
}

string getDot_inode_tree(Inodo _inode, int _index_inode)
{
    string dot =
            string("\"INODE_" + std::to_string(_index_inode) + "\" [ fontsize=\"17\" label = <\n") +
            "<TABLE BGCOLOR=\"#009999\" BORDER=\"2\" COLOR=\"BLACK\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
            "<TR>\n" +
            "<TD BGCOLOR=\"#B8860B\" COLSPAN=\"2\">Inodo " + std::to_string(_index_inode) + " </TD>\n" +
            "</TR>\n" +
            "<TR>\n" +
            "<TD WIDTH=\"130\" BGCOLOR=\"#708090\"><B>Tipo</B></TD>\n" +
            "<TD WIDTH=\"70\" BGCOLOR=\"#797d7f\"> " + _inode.i_type + " </TD>\n" +
            "</TR>\n" +

            "<TR>\n" +
            "<TD WIDTH=\"130\" BGCOLOR=\"#708090\"><B>Tamaño</B></TD>\n" +
            "<TD WIDTH=\"70\" BGCOLOR=\"#797d7f\"> " + std::to_string(_inode.i_size) + " </TD>\n" +
            "</TR>\n" +

            "<TR>\n" +
            "<TD WIDTH=\"130\" BGCOLOR=\"#708090\"><B>Permisos</B></TD>\n" +
            "<TD WIDTH=\"70\" BGCOLOR=\"#797d7f\"> " + std::to_string(_inode.i_perm) + " </TD>\n" +
            "</TR>\n" +
            "\n";
    for (int i = 0; i < 15; i++)
    {
        // if (_inode.i_block[i] != -1)
        dot +=
                string("<TR>\n") +
                "<TD WIDTH=\"130\" BGCOLOR=\"#708090\"><B>i_block[" + std::to_string(i) + "]</B></TD>\n" +
                "<TD PORT=\"PI_" + std::to_string(i) + "\" BGCOLOR=\"#797d7f\">" + std::to_string(_inode.i_block[i]) + "</TD>\n" +
                "</TR>\n\n";
    }
    dot += "</TABLE>>];\n\n";
    for (int i = 0; i < 15; i++)
    {
        if (_inode.i_block[i] != -1)
        {
            dot += "\"INODE_" + std::to_string(_index_inode) + "\":\"PI_" + std::to_string(i) + "\" -> \"BLOCK_" + std::to_string(_inode.i_block[i]) + "\";\n\n";
        }
    }
    return dot;
}

string getDot_folder_block_tree(int _start_blocks, int _index_block, string _path)
{
    FILE *_file = fopen(_path.c_str(), "rb");
    BloqueDeCarpeta cb;
    fseek(_file, _start_blocks, SEEK_SET);
    fseek(_file, _index_block * 64, SEEK_CUR);
    fread(&cb, 64, 1, _file);
    string dot =
            string("\"BLOCK_" + std::to_string(_index_block) + "\" [ fontsize=\"17\" label = <\n") +
            "<TABLE BGCOLOR=\"#009999\" BORDER=\"2\" COLOR=\"BLACK\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
            "<TR>\n" +
            "<TD BGCOLOR=\"#B8860B\" COLSPAN=\"2\">Bloque de carpeta " + std::to_string(_index_block) + "</TD>\n" +
            "</TR>\n" +
            "<TR>\n" +
            "<TD WIDTH=\"130\" BGCOLOR=\"#708090\"><B>b_name</B></TD>\n" +
            "<TD WIDTH=\"70\" BGCOLOR=\"#708090\"><B>b_inodo</B></TD>\n" +
            "</TR>\n" +
            "\n";
    for (int i = 0; i < 4; i++)
    {
        dot +=
                string("<TR>\n") +
                "<TD ALIGN=\"left\">   " + cb.b_content[i].b_name + "</TD>\n" +
                "<TD PORT=\"PB_" + std::to_string(i) + "\">" + std::to_string(cb.b_content[i].b_inodo) + "</TD>\n" +
                "</TR>\n" +
                "\n";
    }
    dot += "</TABLE>>];\n\n";
    for (int i = 0; i < 4; i++)
    {
        if (cb.b_content[i].b_inodo != -1)
            dot += "\"BLOCK_" + std::to_string(_index_block) + "\":\"PB_" + std::to_string(i) + "\" -> \"INODE_" + std::to_string(cb.b_content[i].b_inodo) + "\";\n\n";
    }
    fclose(_file);
    _file = NULL;
    return dot;
}

string getDot_file_block_tree(int _start_blocks, int _index_block, string _path)
{
    FILE *_file = fopen(_path.c_str(), "rb");
    BloqueDeArchivo ab;
    fseek(_file, _start_blocks, SEEK_SET);
    fseek(_file, _index_block * 64, SEEK_CUR);
    fread(&ab, 64, 1, _file);
    string content = string(ab.b_content);
    size_t pos;
    while ((pos = content.find("\n")) != std::string::npos)
        content.replace(pos, 1, "<br/>");
    string dot =
            string("\"BLOCK_" + std::to_string(_index_block) + "\" [ fontsize=\"17\" label = <\n") +
            "<TABLE BGCOLOR=\"#009999\"  BORDER=\"2\" COLOR=\"BLACK\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
            "<TR>\n" +
            "<TD WIDTH=\"190\" BGCOLOR=\"#708090\">Bloque de archivo " + std::to_string(_index_block) + "</TD>\n" +
            "</TR>\n" +
            "\n" +
            "<TR>\n" +
            "<TD>\n";
    dot += (content + "\n");
    dot += string("</TD>\n</TR>\n\n</TABLE>>];\n\n");
    fclose(_file);
    _file = NULL;
    return dot;
}