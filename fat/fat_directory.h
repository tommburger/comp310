#ifndef FAT_DIRECTORY_H
#define FAT_DIRECTORY_H

#include <stdint.h>

#pragma pack(push, 1)

typedef enum file_attr_t {
    ATTR_READ_ONLY    = 0x01,
    ATTR_HIDDEN       = 0x02,
    ATTR_SYSTEM       = 0x04,
    ATTR_VOLUME_ID    = 0x08,
    ATTR_DIRECTORY    = 0x10,
    ATTR_ARCHIVE      = 0x20,
    ATTR_LONG_NAME    = 0x0F
} file_attr_t;

typedef struct fat_dir_entry_t {
    // 0x00
    unsigned char short_file_name[8];
    // 0x08
    unsigned char short_file_ext[3];
    // 0x0B
    uint8_t file_attr;   // type is file_attr_t
    // 0x0C
    uint8_t deleted_file_info;  //??
    // 0x0D
    uint8_t create_time_fine_resolution;  // 10ms units 0-199
    // 0x0E
    uint16_t creation_time;  // sec: 0-4  min: 5-10  hour: 11-15
    // 0x10
    uint16_t creation_date;  // day: 0-4  mon: 5-8   year: 9-15  0=1980
    // 0x12
    uint16_t last_access_date;
    // 0x14
    uint16_t access_rights;
    // 0x16
    uint16_t last_modified_time;
    // 0x18
    uint16_t last_modified_date;
    // 0x1A
    uint16_t starting_cluster;
    // 0x1C
    uint32_t file_size;
} fat_dir_entry_t;

// long file name entry
typedef struct fat_lfn_entry_t {
    // 0x00
    uint8_t seq_num;
    // 0x01
    uint8_t name15[10];
    // 0x0B
    uint8_t file_attr;  // always 0x0f
    // 0x0C
    uint8_t type;   // always 0
    // 0x0D
    uint8_t checksum;
    // 0x0E
    uint8_t name611[12];
    // 0x1A
    uint16_t starting_cluster;   // always 0
    // 0x1C
    uint8_t name1213[4];
} fat_lfn_entry_t;

#pragma pack(pop)

#endif
