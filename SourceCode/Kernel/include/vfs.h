//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_H__
#define __KERNEL_VFS_H__

#include <atomic.h>
#include <list.h>
#include <mutex.h>
#include <spinlock.h>

typedef struct SuperBlock {

} SuperBlock;

typedef enum IndexNodeType {
  INDEX_NODE_DIRECTORY,
  INDEX_NODE_FILE,
} IndexNodeType;

typedef struct IndexNode {
  uint64_t id;

  Mutex mutex;
  uint64_t state;

  IndexNodeType type;
  uint16_t mode;

  uint32_t startAddress;
  uint32_t fileSize;

  Atomic readCount;

  uint64_t createTimestamp;
  uint64_t lastAccessTimestamp;
  uint64_t lastUpdateTimestamp;
} IndexNode;

typedef uint64_t (*DirectoryEntryHashOperation)(const char *);
typedef struct DirectoryEntryOperations {
  DirectoryEntryHashOperation hashOperaction;
} DirectoryEntryOperations;

typedef struct DirectoryEntry {
  struct DirectoryEntry *parent;
  ListNode list;
  IndexNode indexNode;

  Atomic refCount;
  SpinLock parallelLock;

  uint64_t fileNameHash;
  DirectoryEntryOperations *operations;
} DirectoryEntry;

typedef struct File {

} File;

KernelStatus vfs_init();

#endif // __KERNEL_VFS_H__
