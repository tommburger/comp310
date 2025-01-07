#ifndef INODE_H
#define INODE_H

#include <stdint.h>

typedef struct inode_t {
    uint16_t i_mode;
    // complete this declaration
    // page 18 of the Second Extended File System
    // see also https://www.kernel.org/doc/html/latest/filesystems/ext4/inodes.html#i-flags
    // for the extended attributes down through offset 0x9c
} inode_t;

void print_inode(inode_t * inode);
#endif
