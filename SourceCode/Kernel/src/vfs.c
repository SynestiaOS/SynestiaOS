//
// Created by XingfengYang on 2020/7/30.
//

#include <ext2.h>
#include <kheap.h>
#include <vfs.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>

extern char _binary_initrd_img_start[];
extern char _binary_initrd_img_end[];
extern char _binary_initrd_img_size[];
uint32_t EXT2_ADDRESS = _binary_initrd_img_start;

SuperBlock *fileSystems = nullptr;
KernelStatus vfs_init() {
  SuperBlock *root = vfs_mount("/root", FILESYSTEM_EXT2, (void *)EXT2_ADDRESS);
  return OK;
}

SuperBlock *vfs_mount(const char *name, FileSystemType type, void *data) {
  SuperBlock *superBlock = vfs_create_super_block();
  superBlock->fileName = name;
  superBlock->type = type;

  switch (type) {
  case FILESYSTEM_EXT2: {
    Ext2FileSystem ext2FileSystem;
    ext2_init(&ext2FileSystem);
    ext2FileSystem.operations.mount(&ext2FileSystem, superBlock, name, data);
  }
  }

  klist_append(&fileSystems->node, &superBlock->node);
  return superBlock;
}