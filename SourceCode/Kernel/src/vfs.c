//
// Created by XingfengYang on 2020/7/30.
//

#include <ext2.h>
#include <kheap.h>
#include <vfs.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>
#include <string.h>

SuperBlock *vfs_default_mount(VFS *vfs, const char *name, FileSystemType type, void *data) {
  SuperBlock *superBlock = vfs_create_super_block();
  superBlock->name = name;
  superBlock->type = type;

  switch (type) {
    case FILESYSTEM_EXT2: {
      Ext2FileSystem* ext2FileSystem = ext2_create();
      ext2FileSystem->operations.mount(ext2FileSystem, superBlock, name, data);
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

uint32_t vfs_default_open(VFS *vfs, const char *name, uint32_t mode){
  
}

uint32_t vfs_default_read(VFS *vfs, uint32_t fd, char* buffer, uint32_t pos){

}

DirectoryEntry* vfs_default_lookup(VFS *vfs, const char *name){
  // str_split(name,'/')
  SuperBlock* tmpFs = vfs->fileSystems;
  while(tmpFs!=nullptr){
    if(strcmp(tmpFs->name,name)){
      
    }
    if(tmpFs->node.next!=nullptr){
      tmpFs = getNode(&tmpFs->node.next,SuperBlock,node);
    }
    return nullptr;
  }
}

VFS *vfs_create() {
  VFS *vfs = (VFS *)kheap_alloc(sizeof(VFS));
  vfs->fileSystems = nullptr;
  vfs->operations.mount = vfs_default_mount;
  vfs->operations.open = vfs_default_open;
  vfs->operations.read = vfs_default_read;
  vfs->operations.lookup = vfs_default_lookup;
  return vfs;
}
