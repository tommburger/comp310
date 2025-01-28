#ifndef VOLUME_DATA_H
#define VOLUME_DATA_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "boot_sector.h"
#include "fat_directory.h"

enum FilesystemType {UNKNOWN, FAT12, FAT16, FAT32} ;

typedef struct fat_volume_t {
    enum FilesystemType filesystem_type;

    // all 4 boot sector pointers point to the beginning of the volume.
    // Just different views.
    struct common_boot_sector_t * boot;
    struct fat12_boot_sector_t  * boot12;
    struct fat16_boot_sector_t  * boot16;
    struct fat32_boot_sector_t  * boot32;

    // all 3 fat pointers point to the same place.
    // Just different views.
    uint8_t *fat12;
    uint16_t *fat16;
    uint32_t *fat32;

    uint32_t fat_start_location;
    uint32_t fat_sectors;
    uint32_t fat_size;
    uint32_t root_dir_size;
    uint32_t root_dir_sectors;
    uint32_t count_of_clusters;
    uint32_t max_cluster_number;   // count_of_clusters + 2
    uint32_t cluster_size;

    // for the fixed size directory in FAT12 and FAT16
    fat_dir_entry_t * root_dir;

    // the underlying file information
    int filedes;  // the file descriptor for the memory mapped volume file
    size_t volume_size;  // size of the memory mapped volume file

    // memory mapped file used for accessing the volume
    uint8_t * device;

} fat_volume_t;

// open_fat_volume
// 
// initializes a fat_volume_t structure with information from 
// the volume identified by path_name.
// if read_only is true then no modifications should be 
// attempted to the memory mapped volume.
//
// return values:
//  0 - success
//  <0 - error where errno is set
// -1 - cannot open the volume
// -2 - cannot fstat
// -3 - cannot mmap the volume
//  >0 - error where errno is not set
// 1 - volume is too small
// 2 - invalid volume - bad magic number, inconsistent values, ...
// 3 - volume is too small

int open_fat_volume(fat_volume_t * volume, char * path_name, bool read_only);


// close_fat_volume
//
// closes a volume_t structure that was previously opened with open_fat_volume
void close_fat_volume(fat_volume_t * volume);


// print_fat_volume_error
// 
// print a message to standard error describing the error returned
// by open_fat_volume
void print_fat_volume_error(int vol_err);

// print_fat_volume_data
void print_fat_volume_data(fat_volume_t * vol);
#endif
