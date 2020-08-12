//
// Created by XingfengYang & ChengyuZhao on 2020/7/30.
//

#include <log.h>
#include <mutex.h>
#include <spinlock.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>
#include <vfs_super_block.h>

DirectoryEntry *vfs_super_block_default_create_directory_entry(struct SuperBlock *superBlock, const char *fileName) {
  DirectoryEntry *directoryEntry = (DirectoryEntry *)kheap_alloc(sizeof(DirectoryEntry));
  if (directoryEntry == nullptr) {
    LogError("[VFS]: root dentry create failed,cause heap alloc failed.\n");
    return nullptr;
  }
  directoryEntry->superBlock = superBlock;

  directoryEntry->operations.initOperation = vfs_directory_entry_default_init;
  directoryEntry->operations.deleteOperation = vfs_directory_entry_default_delete;
  directoryEntry->operations.getNameOperation = vfs_directory_entry_default_get_name;
  directoryEntry->operations.releaseOperation = vfs_directory_entry_default_release;
  directoryEntry->operations.hashOperation = vfs_directory_entry_default_hash;

  directoryEntry->fileName = fileName;
  directoryEntry->fileNameHash = directoryEntry->operations.hashOperation(directoryEntry);
  directoryEntry->indexNode = nullptr;
  directoryEntry->parent = nullptr;
  directoryEntry->children = nullptr;
  SpinLock parallelLock = SpinLockCreate();
  directoryEntry->parallelLock = parallelLock;
  Atomic atomic = {
      .counter = 0,
  };
  directoryEntry->refCount = atomic;
  directoryEntry->list.next = nullptr;
  directoryEntry->list.prev = nullptr;

  return directoryEntry;
}

IndexNode *vfs_super_block_default_create_index_node(struct SuperBlock *superBlock, struct DirectoryEntry *dentry) {
  IndexNode *indexNode = (IndexNode *)kheap_alloc(sizeof(IndexNode));
  if (indexNode == nullptr) {
    LogError("[VFS]: root inode create failed,cause heap alloc failed.\n");
    return nullptr;
  }
  indexNode->superBlock = superBlock;

  indexNode->operations.createOperation = vfs_inode_default_create;
  indexNode->operations.deleteOperation = vfs_inode_default_delete;
  indexNode->operations.linkOperation = vfs_inode_default_link;
  indexNode->operations.unLinkOperation = vfs_inode_default_unlink;
  indexNode->operations.makeDirectoryOperation = vfs_inode_default_make_directory;
  indexNode->operations.deleteDirectoryOperation = vfs_inode_default_delete_directory;
  indexNode->operations.releaseOperation = vfs_inode_default_release;
  indexNode->operations.renameOperation = vfs_inode_default_rename;

  indexNode->dentry = dentry;
  indexNode->fileSize = 0;
  indexNode->mode = (INDEX_NODE_MODE_WRITEABLE | INDEX_NODE_MODE_READABLE) << 6 |
                    (INDEX_NODE_MODE_WRITEABLE | INDEX_NODE_MODE_READABLE) << 3 |
                    (INDEX_NODE_MODE_WRITEABLE | INDEX_NODE_MODE_READABLE);
  Mutex mutex = MutexCreate();
  indexNode->mutex = mutex;

  Atomic atomic = {
      .counter = 0,
  };
  indexNode->linkCount = atomic;
  indexNode->readCount = atomic;

  indexNode->lastAccessTimestamp = 0;
  indexNode->lastUpdateTimestamp = 0;
  dentry->indexNode = indexNode;

  return indexNode;
}

KernelStatus vfs_super_block_default_destroy_dentry(struct SuperBlock *superBlock, struct DirectoryEntry *dentry) {
  return kheap_free(dentry);
}

KernelStatus vfs_super_block_default_destroy_inode(struct SuperBlock *superBlock, struct IndexNode *indexNode) {
  return kheap_free(indexNode);
}

SuperBlock *vfs_create_super_block() {
  SuperBlock *superBlock = (SuperBlock *)kheap_alloc(sizeof(SuperBlock));
  if (superBlock == nullptr) {
    LogError("[VFS]: root fs mount failed,cause heap alloc failed.\n");
    return nullptr;
  }

  superBlock->operations.createDirectoryEntry = vfs_super_block_default_create_directory_entry;
  superBlock->operations.createIndexNode = vfs_super_block_default_create_index_node;
  superBlock->operations.destroyDirectoryEntry = vfs_super_block_default_destroy_dentry;
  superBlock->operations.destroyIndexNode = vfs_super_block_default_destroy_inode;

  return superBlock;
}
