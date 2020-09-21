//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_SUPER_BLOCK_H__
#define __KERNEL_VFS_SUPER_BLOCK_H__

#include <atomic.h>
#include <list.h>
#include <mutex.h>
#include <spinlock.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>

#define FILE_SYSTEM_NAME_SIZE 32

typedef enum FileSystemType {
    FILESYSTEM_FAT32,
    FILESYSTEM_EXT2,
} FileSystemType;

typedef DirectoryEntry *(*SuperBlockCreateDirectoryEntry)(struct SuperBlock *superBlock, char *fileName);

typedef IndexNode *(*SuperBlockCreateIndexNode)(struct SuperBlock *superBlock, struct DirectoryEntry *dentry);

typedef KernelStatus (*SuperBlockDestroyDirectoryEntry)(struct SuperBlock *superBlock, struct DirectoryEntry *dentry);

typedef KernelStatus (*SuperBlockDestroyIndexNode)(struct SuperBlock *superBlock, struct IndexNode *indexNode);

typedef struct SuperBlockOperations {
    SuperBlockCreateDirectoryEntry createDirectoryEntry;
    SuperBlockCreateIndexNode createIndexNode;
    SuperBlockDestroyDirectoryEntry destroyDirectoryEntry;
    SuperBlockDestroyIndexNode destroyIndexNode;
} SuperBlockOperations;

typedef struct SuperBlock {
    char *name;
    FileSystemType type;
    ListNode node;
    struct DirectoryEntry *rootDirectoryEntry;
    SuperBlockOperations operations;
} SuperBlock;

SuperBlock *vfs_create_super_block();

DirectoryEntry *vfs_super_block_default_create_directory_entry(struct SuperBlock *superBlock, char *fileName);

IndexNode *vfs_super_block_default_create_index_node(struct SuperBlock *superBlock, struct DirectoryEntry *dentry);

KernelStatus vfs_super_block_default_destroy_dentry(struct SuperBlock *superBlock, struct DirectoryEntry *dentry);

KernelStatus vfs_super_block_default_destroy_inode(struct SuperBlock *superBlock, struct IndexNode *indexNode);

#endif// __KERNEL_VFS_SUPER_BLOCK_H__
