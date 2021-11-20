//
// Created by jose on 9/08/21.
//

#ifndef MIA_PROYECTO1_201904061_STRUCTS_H
#define MIA_PROYECTO1_201904061_STRUCTS_H


#include <time.h>

using namespace std;

typedef  struct {
    char part_status;
    char part_type ;
    char part_fit;
    int part_start ;
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

typedef struct {
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    int i_mtime;
    int i_block[15];
    int i_type;
    int i_perm;
} TablaInodos;


#endif //MIA_PROYECTO1_201904061_STRUCTS_H
