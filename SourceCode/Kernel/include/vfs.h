//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_H__
#define __KERNEL_VFS_H__

#include <atomic.h>
#include <list.h>
#include <mutex.h>
#include <spinlock.h>

typedef enum FileSystemType{
    FILESYSTEM_FAT32,
} FileSystemType;


typedef struct SuperBlock {
  FileSystemType type;
} SuperBlock;

typedef enum IndexNodeType {
  INDEX_NODE_DIRECTORY,
  INDEX_NODE_FILE,
} IndexNodeType;

typedef KernelStatus (*IndexNodeDeleteOperation)(struct IndexNode* indexNode);
typedef KernelStatus (*IndexNodeReleaseOperation)( struct IndexNode* indexNode);
typedef KernelStatus (*IndexNodeCreateOperation)( struct IndexNode* indexNode);
typedef KernelStatus (*IndexNodeMakeDirectionOperation)(struct IndexNode* indexNode);
typedef KernelStatus (*IndexNodeRenameOperation)(struct IndexNode* indexNode);
typedef KernelStatus (*IndexNodeHardLinkOperation)(struct IndexNode* indexNode);

typedef struct IndexNodeOpeations{
    IndexNodeCreateOperation createOperation;
    IndexNodeReleaseOperation releaseOperation;
    IndexNodeDeleteOperation deleteOperation;
    IndexNodeMakeDirectionOperation makeDirectionOperation;
    IndexNodeRenameOperation renameOperation;
    IndexNodeHardLinkOperation hardLinkOperation;
} IndexNodeOpeations;

typedef struct IndexNode {
  IndexNodeType type;
  uint64_t id;

  Mutex mutex;
  uint64_t state;

  uint16_t mode;

  uint32_t startAddress;
  uint32_t fileSize;

  Atomic readCount;

  IndexNodeOpeations *operations;

  uint64_t createTimestamp;
  uint64_t lastAccessTimestamp;
  uint64_t lastUpdateTimestamp;
} IndexNode;

typedef uint64_t (*DirectoryEntryHashOperation)(struct DirectoryEntry* directoryEntry,const char *);
typedef char* (*DirectoryEntryGetNameOperaction)(struct DirectoryEntry* directoryEntry);
typedef KernelStatus (*DirectoryEntryDeleteOperation)(struct DirectoryEntry* directory);
typedef KernelStatus (*DirectoryEntryReleaseOperation)(struct DirectoryEntry* directory);
typedef KernelStatus (*DirectoryEntryInitOperation)(struct DirectoryEntry* directory);

typedef struct DirectoryEntryOperations {
  DirectoryEntryInitOperation initOperation;
  DirectoryEntryHashOperation hashOperation;
  DirectoryEntryGetNameOperaction getNameOperation;
  DirectoryEntryDeleteOperation deleteOperation;
  DirectoryEntryReleaseOperation releaseOperation;
} DirectoryEntryOperations;

typedef struct DirectoryEntry {
  struct DirectoryEntry *parent;
  IndexNode *indexNode;
  SuperBlock *superBlock;
  ListNode list;

  Atomic refCount;
  SpinLock parallelLock;

  uint64_t fileNameHash;
  DirectoryEntryOperations *operations;
} DirectoryEntry;

typedef struct File {

} File;

KernelStatus vfs_init();

KernelStatus vfs_mount(const char* name, FileSystemType type);

#endif // __KERNEL_VFS_H__
