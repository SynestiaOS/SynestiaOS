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

typedef enum IndexNodeMode{
  INDEX_NODE_MODE_EXECUTABLE = 0b100,
  INDEX_NODE_MODE_WRITEABLE = 0b010,
  INDEX_NODE_MODE_READABLE = 0b001,
} IndexNodeMode;

typedef KernelStatus (*IndexNodeDeleteOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeReleaseOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeCreateOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeMakeDirectotyOperation)(struct IndexNode *indexNode, const char* fileName, uint16_t mode);
typedef KernelStatus (*IndexNodeRenameOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeHardLinkOperation)(struct IndexNode *indexNode);

typedef struct IndexNodeOpeations {
  IndexNodeCreateOperation createOperation;
  IndexNodeReleaseOperation releaseOperation;
  IndexNodeDeleteOperation deleteOperation;
  IndexNodeMakeDirectotyOperation makeDirectoryOperation;
  IndexNodeRenameOperation renameOperation;
  IndexNodeHardLinkOperation hardLinkOperation;
} IndexNodeOpeations;

typedef struct IndexNode {
  IndexNodeType type;
  uint64_t id;

  struct SuperBlock *superBlock;
  struct DirectoryEntry *dentry;

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


KernelStatus vfs_inode_default_delete(IndexNode *indexNode);

KernelStatus vfs_inode_default_release(IndexNode *indexNode);

KernelStatus vfs_inode_default_create(IndexNode *indexNode);

KernelStatus vfs_inode_default_make_directory(IndexNode *indexNode,const char* fileName,uint16_t mode);

KernelStatus vfs_inode_default_rename(IndexNode *indexNode);

KernelStatus vfs_inode_default_hard_link(IndexNode *indexNode);

#endif // __KERNEL_VFS_INDEX_NODE_H__
