//
// Created by XingfengYang & ChengyuZhao on 2020/7/30.
//

#include <log.h>
#include <vfs_super_block.h>

DirectoryEntry *vfs_super_block_default_create_directory_entry(struct SuperBlock *superBlock) {
  DirectoryEntry *directoryEntry = (DirectoryEntry *)kheap_alloc(sizeof(DirectoryEntry));
  if (directoryEntry == nullptr) {
    LogError("[VFS]: root dentry create failed,cause heap alloc failed.\n");
    return nullptr;
  }
  directoryEntry->superBlock = superBlock;
  return directoryEntry;
}

IndexNode *vfs_super_block_default_create_index_node(struct SuperBlock *superBlock) {
  IndexNode *indexNode = (IndexNode *)kheap_alloc(sizeof(IndexNode));
  if (indexNode == nullptr) {
    LogError("[VFS]: root inode create failed,cause heap alloc failed.\n");
    return nullptr;
  }
  indexNode->superBlock = superBlock;
  return indexNode;
}

SuperBlock *vfs_create_super_block() {
  SuperBlock *superBlock = (SuperBlock *)kheap_alloc(sizeof(SuperBlock));
  if (superBlock == nullptr) {
    LogError("[VFS]: root fs mount failed,cause heap alloc failed.\n");
    return nullptr;
  }
  superBlock->operations->createDirectoryEntry = vfs_super_block_default_create_directory_entry;
  superBlock->operations->createIndexNode = vfs_super_block_default_create_index_node;
}
