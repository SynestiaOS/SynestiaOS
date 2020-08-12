//
// Created by XingfengYang & ChengyuZhao on 2020/7/30.
//

#include <atomic.h>
#include <list.h>
#include <log.h>
#include <vfs_inode.h>
#include <vfs_super_block.h>

KernelStatus vfs_inode_default_release(IndexNode *indexNode) {
  // TODO
  return OK;
}

KernelStatus vfs_inode_default_create(IndexNode *indexNode) {
  // TODO
  return OK;
}

KernelStatus vfs_inode_default_delete(IndexNode *indexNode) {
  // TODO
  return OK;
}

KernelStatus vfs_inode_default_make_directory(IndexNode *indexNode, char *fileName, uint16_t mode) {
  DirectoryEntry *newDir = indexNode->superBlock->operations.createDirectoryEntry(indexNode->superBlock, fileName);
  newDir->parent = indexNode->dentry;
  IndexNode *newNode = indexNode->superBlock->operations.createIndexNode(indexNode->superBlock, newDir);
  newDir->indexNode->type = INDEX_NODE_DIRECTORY;
  newDir->indexNode->mode = mode;
  return OK;
}

KernelStatus vfs_inode_default_delete_directory(IndexNode *indexNode, DirectoryEntry *dentry) {
  if (vfs_inode_default_unlink(indexNode, dentry) != ERROR) {
    if (atomic_get(&dentry->indexNode->linkCount) == 0) {
      // Recursively delete dentrys
    }
    return OK;
  }
  return OK;
}

KernelStatus vfs_inode_default_rename(IndexNode *indexNode, char *newName) {
  indexNode->dentry->fileName = newName;
  indexNode->dentry->fileNameHash = indexNode->dentry->operations.hashOperation(indexNode->dentry);
  // TODO : change last modify time
  return OK;
}

KernelStatus vfs_inode_default_link(IndexNode *indexNode, DirectoryEntry *dentry) {
  dentry->indexNode = indexNode;
  klist_append(&indexNode->dentry->list, &dentry->list);
  atomic_inc(&indexNode->linkCount);
  return OK;
}

KernelStatus vfs_inode_default_unlink(IndexNode *indexNode, DirectoryEntry *dentry) {
  if (atomic_get(&dentry->indexNode->linkCount) > 1) {
    atomic_dec(&dentry->indexNode->linkCount);
    dentry->operations.deleteOperation(dentry);
  }
  return OK;
}
