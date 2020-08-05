//
// Created by XingfengYang & ChengyuZhao on 2020/7/30.
//

#include <log.h>
#include <vfs_super_block.h>
#include <vfs_inode.h>
#include <vfs_dentry.h>

DirectoryEntry *vfs_super_block_default_create_directory_entry(struct SuperBlock *superBlock) {
  DirectoryEntry *directoryEntry = (DirectoryEntry *)kheap_alloc(sizeof(DirectoryEntry));
  if (directoryEntry == nullptr) {
    LogError("[VFS]: root dentry create failed,cause heap alloc failed.\n");
    return nullptr;
  }
  directoryEntry->superBlock = superBlock;
  directoryEntry->operations->initOperation = vfs_directory_entry_default_init;
  directoryEntry->operations->deleteOperation = vfs_directory_entry_default_delete;
  directoryEntry->operations->getNameOperation = vfs_directory_entry_default_get_name;
  directoryEntry->operations->releaseOperation = vfs_directory_entry_default_release;
  directoryEntry->operations->hashOperation = vfs_directory_entry_default_hash;
  return directoryEntry;
}

IndexNode *vfs_super_block_default_create_index_node(struct SuperBlock *superBlock, struct DirectoryEntry *dentry) {
  IndexNode *indexNode = (IndexNode *)kheap_alloc(sizeof(IndexNode));
  if (indexNode == nullptr) {
    LogError("[VFS]: root inode create failed,cause heap alloc failed.\n");
    return nullptr;
  }
  indexNode->superBlock = superBlock;
  indexNode->dentry = dentry;
  dentry->indexNode = indexNode;
  indexNode->operations->createOperation = vfs_inode_default_create;
  indexNode->operations->deleteOperation = vfs_inode_default_delete;
  indexNode->operations->hardLinkOperation = vfs_inode_default_hard_link;
  indexNode->operations->makeDirectoryOperation = vfs_inode_default_make_directory;
  indexNode->operations->releaseOperation = vfs_inode_default_release;
  indexNode->operations->renameOperation = vfs_inode_default_rename;
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
