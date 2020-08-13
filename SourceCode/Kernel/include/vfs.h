//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_H__
#define __KERNEL_VFS_H__

#include <atomic.h>
#include <kvector.h>
#include <list.h>
#include <mutex.h>
#include <spinlock.h>
#include <vfs_super_block.h>

typedef struct OpenFile {
  uint32_t offset;
  uint32_t state;
  uint32_t indexNode;
} OpenFile;

typedef SuperBlock *(*VFSOperationMount)(struct VFS *vfs, const char *name, FileSystemType type, void *data);
typedef uint32_t (*VFSOperationOpen)(struct VFS *vfs, const char *name, uint32_t mode);
typedef DirectoryEntry* (*VFSOperationLookUp)(struct VFS *vfs, const char *name);
typedef uint32_t (*VFSOperationRead)(struct VFS *vfs, uint32_t fd, char* buffer, uint32_t pos);
typedef struct VFSOperations {
  VFSOperationMount mount;
  VFSOperationOpen open;
  VFSOperationRead read;
  VFSOperationLookUp lookup;
} VFSOperations;

typedef struct VFS {
  struct SuperBlock *fileSystems;
  KernelVector *openFileTable;
  VFSOperations operations;
} VFS;

VFS *vfs_create();

#endif // __KERNEL_VFS_H__
