//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_INDEX_NODE_H__
#define __KERNEL_VFS_INDEX_NODE_H__

#include <atomic.h>
#include <list.h>
#include <mutex.h>
#include <spinlock.h>

typedef enum IndexNodeType {
  INDEX_NODE_DIRECTORY,
  INDEX_NODE_FILE,
} IndexNodeType;

typedef KernelStatus (*IndexNodeDeleteOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeReleaseOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeCreateOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeMakeDirectionOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeRenameOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeHardLinkOperation)(struct IndexNode *indexNode);

typedef struct IndexNodeOpeations {
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

  SuperBlock *superBlock;

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

#endif // __KERNEL_VFS_INDEX_NODE_H__
