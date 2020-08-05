//
// Created by XingfengYang on 2020/7/30.
//

#include <kheap.h>
#include <vfs.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>

SuperBlock *fileSystems = nullptr;
KernelStatus vfs_init() {
  SuperBlock *root = vfs_mount("rootfs", FILESYSTEM_FAT32);
  return OK;
}

SuperBlock *vfs_mount(const char *name, FileSystemType type) {
  SuperBlock *superBlock = vfs_create_super_block();
  superBlock->fileName = name;
  superBlock->type = type;

  DirectoryEntry *rootDirectoryEntry = superBlock->operations->createDirectoryEntry(superBlock);
  IndexNode *rootIndexNode = superBlock->operations->createIndexNode(superBlock,rootDirectoryEntry);
  rootDirectoryEntry->operations->initOperation(rootDirectoryEntry, nullptr, rootIndexNode);
  rootDirectoryEntry->fileName = "/";

  klist_append(&fileSystems->node, &superBlock->node);
  return superBlock;
}