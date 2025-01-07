#ifndef VOLUME_H
#define VOLUME_H

#include "superblock.h"
#include "block_group.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// collection of data about a volume.
typedef struct volume_t {
    // memory mapped file used for accessing the volume
    uint8_t * device;

    // The superblock starts at an offset of 1024 from the 
    // start of the device
    struct superblock_t * super;

    // the number of block groups is determined from info 
    // in the super block.  There is an array of block groups.
    uint32_t num_block_groups;
    struct block_group_t * blk_groups;

    // data calculated from information in the superblock
    uint32_t block_size;  // 1024 << super.s_log_block_size

    // the underlying file information
    int filedes;  // the file descriptor for the memory mapped volume file
    size_t volume_size;  // size of the memory mapped volume file
} volume_t;

// open_volume
//
// initializes a volume_t structure with information from
// the volume identified by path_name.
// if read_only is true then no modifications should be 
// attempted to the memory mapped volume.
//
// return values:
//  0 - success
//  anything else means failure

int open_volume(volume_t * volume, char * path_name, bool read_only);


// close_volume
//
// closes a volume_t structure that was previously opened with open_volume
void close_volume(volume_t * volume);

#endif
