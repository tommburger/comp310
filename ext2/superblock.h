#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <stdint.h>

typedef struct superblock_t {
    uint32_t s_inodes_count;
    // complete this declaration.
    // See page 7 of The Second Extended File System
} superblock_t;

void print_superblock(superblock_t * super);

#endif
