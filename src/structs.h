//
// Created by jose on 9/08/21.
//

#ifndef MIA_PROYECTO1_201904061_STRUCTS_H
#define MIA_PROYECTO1_201904061_STRUCTS_H


#include <time.h>

using namespace std;

typedef  struct {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
} Partition;

typedef struct {
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    char disk_fit;
    Partition mbr_partition[4];
} MBR;

typedef struct {
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
} EBR;

typedef struct {
    int start;
    int size;
} PartitionHole;

typedef struct {
    string id;
    string path;
    Partition partition;
} MountedPartition;


typedef struct {
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
} SuperBloque;

struct Journaling {
    char command[100] = "-";
};

typedef struct {
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    int i_mtime;
    int i_block[15];
    char i_type;
    int i_perm;
} Inodo;

struct ContentDeCarpeta {
    char b_name[12] = "";   // Nombre de la carpeta o archivo
    int b_inodo = -1;       // Apuntador hacia un inodo asociado al archivo o carpeta
};

struct BloqueDeCarpeta {
    ContentDeCarpeta b_content[4];  // Array con el contenido de la carpeta
};

struct BloqueDeArchivo {
    char b_content[64]; // Array con el contenido del archivo
};

struct BloqueDePunteros {
    int b_pointers[16]; // Array con apuntadores hacia bloques (de archivos o corpteas)
};


struct Usuario {
    int uid = 1;
    string nombre = "root";
    string contrasena = "123";
    string grupo = "root";
    MountedPartition mountedPartition;
    bool logeado = false;
};

#endif //MIA_PROYECTO1_201904061_STRUCTS_H
