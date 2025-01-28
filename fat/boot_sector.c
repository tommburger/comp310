#include "boot_sector.h"
#include <stdio.h>

static void print_common_boot_sector(common_boot_sector_t * boot)
{
    printf("BOOT Sector\n"
           "oem name: %8s  bytes/sector: %d sectors/cluster: %d "
           "reserved sectors: %d\n",
           boot->oem_name,
           boot->bytes_per_sector,
           boot->sectors_per_cluster,
           boot->reserved_sectors);
    printf("fat copies: %d   root dir entries: %d   sectors in filesystem: %d\n",
           boot->fat_copies,
           boot->root_dir_entries,
           boot->sectors_in_filesystem);
    printf("media descriptor: %02x   sectors/fat: %d   sectors/track: %d   heads: %d\n",
           boot->media_descriptor_type,
           boot->sectors_per_fat,
           boot->sectors_per_track,
           boot->heads);
}

void print_fat12_boot_sector(fat12_boot_sector_t * boot12)
{
    print_common_boot_sector(&boot12->common);
    printf("FAT12 specific    hidden sectors: %d\n", boot12->hidden_sectors);
}

void print_fat16_boot_sector(fat16_boot_sector_t * boot16)
{
    print_common_boot_sector(&boot16->common);
    printf("FAT16 specific    hidden sectors: %d\n", boot16->hidden_sectors);
    printf("sectors in filesystem: %d  serial number:  %08x\n",
           boot16->sectors_in_filesystem,
           boot16->serial_number);
    printf("filesystem type: %.8s   volume label: %.11s\n",
           boot16->filesystem_type,
           boot16->volume_label);
}

void print_fat32_boot_sector(fat32_boot_sector_t * boot32)
{
    print_common_boot_sector(&boot32->common);
    printf("FAT32 specific    hidden sectors: %d\n", boot32->hidden_sectors);
    printf("sectors in filesystem: %d  serial number: %08x  sectors/fat: %d\n",
           boot32->sectors_in_filesystem,
           boot32->serial_number,
           boot32->sectors_per_fat);
    printf("filesystem version: %04x  first cluster of root dir: %d\n",
           boot32->filesystem_version,
           boot32->first_cluster_of_root_directory);
    printf("filesystem type: %.8s   volume label: %.11s\n",
           boot32->filesystem_type,
           boot32->volume_label);
}

