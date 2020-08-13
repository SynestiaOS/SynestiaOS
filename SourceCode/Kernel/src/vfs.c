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

char peek(char *src,uint32_t index, uint32_t offset){
  return src[index + offset];
}

char consume(char *src, uint32_t index){
  return src[index++];
}

DirectoryEntry* vfs_default_lookup(VFS *vfs, const char *name){
  
  typedef enum PathLookUpState{
    PATH_LOOKUP_START,
    PATH_LOOKUP_DOT,
    PATH_LOOKUP_SLASH,
    PATH_LOOKUP_NAME,
  } PathLookUpState;

  PathLookUpState lookupState = PATH_LOOKUP_START;
  uint32_t index = 0;
  uint32_t length = strlen(name);

  while(index < length){
    char currentChr = consume(name, index);
    switch(lookupState){
      case PATH_LOOKUP_START:{
        if(currentChr=='.'){
          lookupState = PATH_LOOKUP_DOT;
        }else if(currentChr=='/'){
          lookupState = PATH_LOOKUP_SLASH;
        }else{
          lookupState = PATH_LOOKUP_NAME;
        }
        break;
      }
      case PATH_LOOKUP_DOT:{
        if(currentChr=='/'){
          lookupState = PATH_LOOKUP_SLASH;
        }else if(currentChr =='.'){
          if(peek(name,index,0)=='/'){
            lookupState = PATH_LOOKUP_SLASH;
            index++;
          }else{
            // illegal path
          }
        }else{
          lookupState = PATH_LOOKUP_NAME;
        }
        break;
      }
      case PATH_LOOKUP_SLASH:{
        if(currentChr=='/'){
          lookupState = PATH_LOOKUP_SLASH;
        }else if(currentChr =='.'){
          lookupState = PATH_LOOKUP_DOT;
        }else{
          lookupState = PATH_LOOKUP_NAME;
        }
        break;
      }
      case PATH_LOOKUP_NAME:{
        if(currentChr=='/'){
          lookupState = PATH_LOOKUP_SLASH;
        }else{
          // illegal path
        }
        break;
      } 
      default:
        // illegal path
        break;
    }
  }

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
