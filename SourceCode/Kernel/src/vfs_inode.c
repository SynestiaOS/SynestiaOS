//
// Created by XingfengYang & ChengyuZhao on 2020/7/30.
//

#include <log.h>
#include <vfs_inode.h>
#include <vfs_super_block.h>

KernelStatus vfs_inode_default_delete(IndexNode *indexNode) {
  // todo
  return OK;
}

KernelStatus vfs_inode_default_release(IndexNode *indexNode) {
  // todo
  return OK;
}

KernelStatus vfs_inode_default_create(IndexNode *indexNode) {
  // todo
  return OK;
}

KernelStatus vfs_inode_default_make_directory(IndexNode *indexNode, const char *fileName, uint16_t mode) {
  DirectoryEntry *newDir = indexNode->superBlock->operations->createDirectoryEntry(indexNode->superBlock, fileName);
  newDir->parent = indexNode->dentry;
  IndexNode *newNode = indexNode->superBlock->operations->createIndexNode(indexNode->superBlock, newDir);
  newDir->indexNode->type = INDEX_NODE_DIRECTORY;
  newDir->indexNode->mode = mode;
  return OK;
}

KernelStatus vfs_inode_default_rename(IndexNode *indexNode) {
  // todo
  return OK;
}

KernelStatus vfs_inode_default_hard_link(IndexNode *indexNode) {
  // todo
  return OK;
}
