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

typedef DirectoryEntry *(*SuperBlockCreateDirectoryEntry)(struct SuperBlock *superBlock, const char *fileName);
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
  char *fileName;
  FileSystemType type;
  ListNode node;
  struct DirectoryEntry *rootDirectoryEntry;
  SuperBlockOperations *operations;
} SuperBlock;

SuperBlock *vfs_create_super_block();

#endif // __KERNEL_VFS_SUPER_BLOCK_H__
