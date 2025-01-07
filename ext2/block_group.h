#ifndef BLOCK_GROUP_H
#define BLOCK_GROUP_H

#include <stdint.h>

typedef struct block_group_t {
    uint32_t bg_block_bitmap;
    // complete the definition of the block group structure
    // page 16 of The Second Extended File System
} block_group_t;

void print_block_group(block_group_t * bg, int num_block_groups);

#endif
