#ifndef BOOT_SECTOR_H
#define BOOT_SECTOR_H

#include <stdint.h>

#pragma pack(push, 1)

// the first part of the boot sector is common across
// all three types of fat filesystems.
typedef struct common_boot_sector_t {
    uint8_t jmp[3];
    char    oem_name[8];
    uint16_t bytes_per_sector;
    uint8_t  sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t  fat_copies;
    uint16_t root_dir_entries;
    uint16_t sectors_in_filesystem;
    uint8_t  media_descriptor_type;
    uint16_t sectors_per_fat;
    uint16_t sectors_per_track;
    uint16_t heads;
} common_boot_sector_t;

typedef struct fat12_boot_sector_t {
    common_boot_sector_t common;
    uint16_t hidden_sectors;
    uint8_t  bootstrap[480];
    uint16_t signature;
} fat12_boot_sector_t;

typedef struct fat16_boot_sector_t {
    common_boot_sector_t common;
    uint32_t hidden_sectors;
    uint32_t sectors_in_filesystem;
    uint8_t  logical_drive;
    uint8_t  reserved;
    uint8_t  extended_signature;  // 0x29 indicates presence of next 3 fields
    uint32_t serial_number;
    char     volume_label[11];
    char     filesystem_type[8];
    uint8_t  bootstrap[448];
    uint16_t signature;
} fat16_boot_sector_t;

typedef struct fat32_boot_sector_t {
    common_boot_sector_t common;
    uint32_t hidden_sectors;
    uint32_t sectors_in_filesystem;
    uint32_t sectors_per_fat;
    uint16_t mirror_flags;
    uint16_t filesystem_version;
    uint32_t first_cluster_of_root_directory;
    uint16_t filesystem_information_sector;
    uint16_t backup_boot_sector_location;
    char     reserved_1[12];
    uint8_t  logical_drive;
    char     reserved_2;
    uint8_t  extended_signature;  // 0x29 indicates presence of next 3 fields
    uint32_t serial_number;
    char     volume_label[11];
    char     filesystem_type[8];
    uint8_t  bootstrap[420];
    uint16_t signature;
} fat32_boot_sector_t;

#pragma pack(pop)

void print_fat12_boot_sector(fat12_boot_sector_t * boot12);
void print_fat16_boot_sector(fat16_boot_sector_t * boot16);
void print_fat32_boot_sector(fat32_boot_sector_t * boot32);

#endif
