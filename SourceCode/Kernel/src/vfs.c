//
// Created by XingfengYang on 2020/7/30.
//

#include <ext2.h>
#include <kheap.h>
#include <log.h>
#include <string.h>
#include <vfs.h>
#include <vfs_dentry.h>
#include <vfs_inode.h>

SuperBlock *vfs_default_mount(VFS *vfs, const char *name, FileSystemType type, void *data) {
  SuperBlock *superBlock = vfs_create_super_block();
  superBlock->name = name;
  superBlock->type = type;

  switch (type) {
  case FILESYSTEM_EXT2: {
    Ext2FileSystem *ext2FileSystem = ext2_create();
    superBlock->type = FILESYSTEM_EXT2;
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

uint32_t vfs_default_open(VFS *vfs, const char *name, uint32_t mode) {
  DirectoryEntry *directoryEntry = vfs->operations.lookup(vfs, name);
  if (directoryEntry == nullptr) {
    LogError("[VFS]: file '%s' not found.\n", name);
    return 0;
  }
  //    atomic_inc(&directoryEntry->indexNode->readCount);
  directoryEntry->indexNode->state = INDEX_NODE_STATE_OPENED;

  // allocat a open file item
  OpenFile *openFile = (OpenFile *)kheap_alloc(sizeof(OpenFile));
  openFile->node.next = nullptr;
  openFile->node.prev = nullptr;
  openFile->indexNode = (uint32_t)directoryEntry->indexNode;
  openFile->state = 0;
  openFile->offset = 0;

  // add to vfs's open table
  kvector_add(vfs->openFileTable, &openFile->node);

  if (directoryEntry->superBlock->type == FILESYSTEM_EXT2) {

    Ext2IndexNode *ext2IndexNode = (Ext2IndexNode *)directoryEntry->indexNode->indexNodePrivate;

    return ext2IndexNode->sizeUpper32Bits << 32 | ext2IndexNode->sizeLower32Bits;
  }

  return 0;
}

uint32_t vfs_default_read(VFS *vfs, uint32_t fd, char *buffer, uint32_t pos) {}

char peek(char *src, uint32_t index, uint32_t offset) { return src[index + offset]; }

DirectoryEntry *vfs_default_lookup(VFS *vfs, const char *name) {

  typedef enum PathLookUpState {
    PATH_LOOKUP_START,
    PATH_LOOKUP_DOT,
    PATH_LOOKUP_SLASH,
    PATH_LOOKUP_NAME,
  } PathLookUpState;

  PathLookUpState lookupState = PATH_LOOKUP_START;
  uint32_t bufStart = 0;
  uint32_t index = 0;
  uint32_t length = strlen(name);

  DirectoryEntry *currentDirectory = vfs->fileSystems->rootDirectoryEntry;

  while (index <= length) {
    char currentChr = peek(name, index, 0);
    index++;
    switch (lookupState) {
    case PATH_LOOKUP_START: {
      if (currentChr == '.') {
        lookupState = PATH_LOOKUP_DOT;
      } else if (currentChr == '/') {
        lookupState = PATH_LOOKUP_SLASH; // /
        LogWarn("[LookUp]: root\n");
        currentDirectory = vfs->fileSystems->rootDirectoryEntry;
      } else {
        lookupState = PATH_LOOKUP_NAME; // name
        bufStart = index - 1;
      }
      break;
    }
    case PATH_LOOKUP_DOT: {
      if (currentChr == '/') {
        lookupState = PATH_LOOKUP_SLASH; // ./
        LogWarn("[LookUp]: current\n");
        currentDirectory = currentDirectory;
      } else if (currentChr == '.') {
        if (peek(name, index, 0) == '/') {
          lookupState = PATH_LOOKUP_SLASH; // ../
          LogWarn("[LookUp]: up\n");
          if (currentDirectory->parent != nullptr) {
            currentDirectory = currentDirectory->parent;
          } else {
            currentDirectory = vfs->fileSystems->rootDirectoryEntry;
          }
          index++;
        } else {
          // illegal path
        }
      } else {
        lookupState = PATH_LOOKUP_NAME;
      }
      break;
    }
    case PATH_LOOKUP_SLASH: {
      if (currentChr == '/') {
        lookupState = PATH_LOOKUP_SLASH; // //
        LogWarn("[LookUp]: root\n");
        currentDirectory = vfs->fileSystems->rootDirectoryEntry;
      } else if (currentChr == '.') {
        lookupState = PATH_LOOKUP_DOT;
      } else {
        lookupState = PATH_LOOKUP_NAME;
        bufStart = index - 1;
      }
      break;
    }
    case PATH_LOOKUP_NAME: {
      if (currentChr == '/') {
        lookupState = PATH_LOOKUP_SLASH; // name/
        char path[index - bufStart];
        for (uint32_t i = 0; i < index - bufStart; i++) {
          path[i] = name[bufStart + i];
        }
        path[index - bufStart - 1] = '\0';
        LogWarn("[LookUp]: %s \n", path);
        ListNode *tmpNode = &(currentDirectory->children->list);
        bool isFound = false;
        while (tmpNode != nullptr) {
          DirectoryEntry *tmpDirectoryEntry = getNode(tmpNode, DirectoryEntry, list);
          LogInfo("[LookUp]: %s \n", tmpDirectoryEntry->fileName);
          if (strcmp(tmpDirectoryEntry->fileName, path)) {
            currentDirectory = tmpDirectoryEntry;
            isFound = true;
            break;
          }
          if (tmpNode->prev != nullptr) {
            tmpNode = tmpNode->prev;
          } else {
            break;
          }
        }
        if (!isFound) {
          // not found
          char path[index];
          for (uint32_t i = 0; i < index; i++) {
            path[i] = name[i];
          }
          path[index] = '\0';
          LogError("[LookUp]: %s not found.\n", path);
          return nullptr;
        }
      } else if (index == length) {
        lookupState = PATH_LOOKUP_SLASH; // name/
        char path[index - bufStart];
        for (uint32_t i = 0; i < index - bufStart; i++) {
          path[i] = name[bufStart + i];
        }
        path[index - bufStart] = '\0';
        LogWarn("[LookUp]: %s \n", path);
        ListNode *tmpNode = &(currentDirectory->children->list);
        bool isFound = false;
        while (tmpNode != nullptr) {
          DirectoryEntry *tmpDirectoryEntry = getNode(tmpNode, DirectoryEntry, list);
          LogInfo("[LookUp]: %s \n", tmpDirectoryEntry->fileName);
          if (strcmp(tmpDirectoryEntry->fileName, path)) {
            currentDirectory = tmpDirectoryEntry;
            isFound = true;
            break;
          }
          if (tmpNode->prev != nullptr) {
            tmpNode = tmpNode->prev;
          } else {
            break;
          }
        }
        if (!isFound) {
          // not found
          char path[index];
          for (uint32_t i = 0; i < index; i++) {
            path[i] = name[i];
          }
          path[index] = '\0';
          LogError("[LookUp]: %s not found.\n", path);
          return nullptr;
        }
      } else {
        // illegal path
      }
      break;
    }
    }
  }

  return currentDirectory;
}

VFS *vfs_create() {
  VFS *vfs = (VFS *)kheap_alloc(sizeof(VFS));
  vfs->fileSystems = nullptr;
  vfs->openFileTable = kvector_allocate();
  vfs->operations.mount = vfs_default_mount;
  vfs->operations.open = vfs_default_open;
  vfs->operations.read = vfs_default_read;
  vfs->operations.lookup = vfs_default_lookup;
  return vfs;
}
