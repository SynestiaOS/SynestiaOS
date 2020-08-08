//
// Created by XingfengYang on 2020/8/7.
//

#ifndef __KERNEL_FS_EXT2_H__
#define __KERNEL_FS_EXT2_H__
#include <stdint.h>

#define EXT2_NAME_LENGTH 255

typedef struct Ext2DirectoryEntry{
    uint32_t indexNode;
    uint16_t directoryEntryLength;
    uint8_t nameLength;
    uint8_t fileType;
    char name[EXT2_NAME_LENGTH];
} Ext2DirectoryEntry;

typedef enum Ext2FileType{
    EXT2_FILE_TYPE_UNKNOWN,
    EXT2_FILE_TYPE_REGFILE,
    EXT2_FILE_TYPE_DIR,
    EXT2_FILE_TYPE_CHRDEV,
    EXT2_FILE_TYPE_BLKDEV,
    EXT2_FILE_TYPE_FIFO,
    EXT2_FILE_TYPE_SOCK,
    EXT2_FILE_TYPE_SYMLINK,
    EXT2_FILE_TYPE_MAX
}Ext2FileType;


#endif // __KERNEL_FS_EXT2_H__