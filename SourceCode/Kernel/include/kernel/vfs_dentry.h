//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_DIRECTORY_ENTRY_H__
#define __KERNEL_VFS_DIRECTORY_ENTRY_H__

#include "kernel/atomic.h"
#include "kernel/list.h"
#include "kernel/mutex.h"
#include "kernel/spinlock.h"

typedef uint64_t (*DirectoryEntryHashOperation)(struct DirectoryEntry *directoryEntry);

typedef char *(*DirectoryEntryGetNameOperation)(struct DirectoryEntry *directoryEntry);

typedef KernelStatus (*DirectoryEntryDeleteOperation)(struct DirectoryEntry *directory);

typedef KernelStatus (*DirectoryEntryReleaseOperation)(struct DirectoryEntry *directory);

typedef KernelStatus (*DirectoryEntryInitOperation)(struct DirectoryEntry *directory, struct DirectoryEntry *parent,
                                                    struct IndexNode *inode);

typedef struct DirectoryEntryOperations {
    DirectoryEntryInitOperation initOperation;
    DirectoryEntryHashOperation hashOperation;
    DirectoryEntryGetNameOperation getNameOperation;
    DirectoryEntryDeleteOperation deleteOperation;
    DirectoryEntryReleaseOperation releaseOperation;
} DirectoryEntryOperations;

typedef struct DirectoryEntry {
    struct DirectoryEntry *parent;
    struct DirectoryEntry *children;
    struct IndexNode *indexNode;
    struct SuperBlock *superBlock;

    ListNode list;

    Atomic refCount;
    SpinLock parallelLock;

    char fileName[0xFF];
    uint64_t fileNameHash;
    DirectoryEntryOperations operations;
} DirectoryEntry;

uint64_t vfs_directory_entry_default_hash(DirectoryEntry *DirectoryEntry);

char *vfs_directory_entry_default_get_name(DirectoryEntry *directoryEntry);

KernelStatus vfs_directory_entry_default_delete(DirectoryEntry *directory);

KernelStatus vfs_directory_entry_default_release(DirectoryEntry *directory);

KernelStatus vfs_directory_entry_default_init(DirectoryEntry *directory, DirectoryEntry *parent,
                                              struct IndexNode *inode);

#endif// __KERNEL_VFS_DIRECTORY_ENTRY_H__
