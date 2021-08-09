//
// Created by jose on 9/08/21.
//

#ifndef MIA_PROYECTO1_201904061_STRUCTS_H
#define MIA_PROYECTO1_201904061_STRUCTS_H


#include <time.h>

typedef  struct {
    char part_status;
    char part_type = 'p';
    char part_fit = 'f';
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



#endif //MIA_PROYECTO1_201904061_STRUCTS_H
