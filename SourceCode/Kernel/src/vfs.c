//
// Created by XingfengYang on 2020/7/30.
//

#include <ext2.h>
#include <kheap.h>
#include <vfs.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>

SuperBlock *vfs_default_mount(VFS *vfs, const char *name, FileSystemType type, void *data) {
  SuperBlock *superBlock = vfs_create_super_block();
  superBlock->fileName = name;
  superBlock->type = type;

  switch (type) {
  case FILESYSTEM_EXT2: {
    Ext2FileSystem ext2FileSystem;
    ext2_init(&ext2FileSystem);
    ext2FileSystem.operations.mount(&ext2FileSystem, superBlock, name, data);
    break;
  }
  }

  if (vfs->fileSystems == nullptr) {
    vfs->fileSystems = superBlock;
  } else {
    klist_append(&vfs->fileSystems->node, &superBlock->node);
  }
  return superBlock;
}

VFS *vfs_create() {
  VFS *vfs = (VFS *)kheap_alloc(sizeof(VFS));
  vfs->fileSystems = nullptr;
  vfs->operations.mount = vfs_default_mount;
  return vfs;
}
