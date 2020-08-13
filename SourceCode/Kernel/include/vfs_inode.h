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

typedef enum IndexNodeMode {
  INDEX_NODE_MODE_EXECUTABLE = 0b100,
  INDEX_NODE_MODE_WRITEABLE = 0b010,
  INDEX_NODE_MODE_READABLE = 0b001,
} IndexNodeMode;

typedef KernelStatus (*IndexNodeDeleteOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeReleaseOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeCreateOperation)(struct IndexNode *indexNode);
typedef KernelStatus (*IndexNodeMakeDirectotyOperation)(struct IndexNode *indexNode, char *fileName, uint16_t mode);
typedef KernelStatus (*IndexNodeDeleteDirectotyOperation)(struct IndexNode *indexNode, struct DirectoryEntry *dentry);
typedef KernelStatus (*IndexNodeRenameOperation)(struct IndexNode *indexNode, char *newName);
typedef KernelStatus (*IndexNodeLinkOperation)(struct IndexNode *indexNode, struct DirectoryEntry *dentry);
typedef KernelStatus (*IndexNodeUnLinkOperation)(struct IndexNode *indexNode, struct DirectoryEntry *dentry);

typedef struct IndexNodeOperations {
  IndexNodeCreateOperation createOperation;
  IndexNodeReleaseOperation releaseOperation;
  IndexNodeDeleteOperation deleteOperation;
  IndexNodeMakeDirectotyOperation makeDirectoryOperation;
  IndexNodeDeleteDirectotyOperation deleteDirectoryOperation;
  IndexNodeRenameOperation renameOperation;
  IndexNodeLinkOperation linkOperation;
  IndexNodeUnLinkOperation unLinkOperation;
} IndexNodeOperations;

typedef enum IndexNodeState {
  INDEX_NODE_STATE_OPENED,
} IndexNodeState;
typedef struct IndexNode {
  IndexNodeType type;
  uint32_t id;

  struct SuperBlock *superBlock;
  struct DirectoryEntry *dentry;

  Mutex mutex;
  uint32_t state;

  uint16_t mode;

  uint32_t startAddress;
  uint32_t indexNodePrivate;
  uint32_t fileSize;

  Atomic readCount;
  Atomic linkCount;

  IndexNodeOperations operations;

  uint32_t createTimestamp;
  uint32_t lastAccessTimestamp;
  uint32_t lastUpdateTimestamp;
} IndexNode;

KernelStatus vfs_inode_default_release(IndexNode *indexNode);

KernelStatus vfs_inode_default_create(IndexNode *indexNode);

KernelStatus vfs_inode_default_delete(IndexNode *indexNode);

KernelStatus vfs_inode_default_make_directory(IndexNode *indexNode, char *fileName, uint16_t mode);

KernelStatus vfs_inode_default_delete_directory(IndexNode *indexNode, struct DirectoryEntry *dentry);

KernelStatus vfs_inode_default_rename(IndexNode *indexNode, char *newName);

KernelStatus vfs_inode_default_link(IndexNode *indexNode, struct DirectoryEntry *dentry);

KernelStatus vfs_inode_default_unlink(IndexNode *indexNode, struct DirectoryEntry *dentry);

#endif // __KERNEL_VFS_INDEX_NODE_H__
