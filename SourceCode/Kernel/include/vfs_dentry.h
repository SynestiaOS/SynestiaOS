//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_DIRECTORY_ENTRY_H__
#define __KERNEL_VFS_DIRECTORY_ENTRY_H__

#include <atomic.h>
#include <list.h>
#include <mutex.h>
#include <spinlock.h>

typedef uint64_t (*DirectoryEntryHashOperation)(struct DirectoryEntry *directoryEntry, const char *name);
typedef char *(*DirectoryEntryGetNameOperaction)(struct DirectoryEntry *directoryEntry);
typedef KernelStatus (*DirectoryEntryDeleteOperation)(struct DirectoryEntry *directory);
typedef KernelStatus (*DirectoryEntryReleaseOperation)(struct DirectoryEntry *directory);
typedef KernelStatus (*DirectoryEntryInitOperation)(struct DirectoryEntry *directory, struct DirectoryEntry *parent,
                                                    struct IndexNode *inode);

typedef struct DirectoryEntryOperations {
  DirectoryEntryInitOperation initOperation;
  DirectoryEntryHashOperation hashOperation;
  DirectoryEntryGetNameOperaction getNameOperation;
  DirectoryEntryDeleteOperation deleteOperation;
  DirectoryEntryReleaseOperation releaseOperation;
} DirectoryEntryOperations;

typedef struct DirectoryEntry {
  struct DirectoryEntry *parent;
  struct IndexNode *indexNode;
  struct SuperBlock *superBlock;
  ListNode list;

  Atomic refCount;
  SpinLock parallelLock;

  char *fileName;
  uint64_t fileNameHash;
  DirectoryEntryOperations *operations;
} DirectoryEntry;

#endif // __KERNEL_VFS_DIRECTORY_ENTRY_H__
