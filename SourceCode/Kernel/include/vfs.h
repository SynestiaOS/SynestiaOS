//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_H__
#define __KERNEL_VFS_H__

#include <atomic.h>
#include <list.h>
#include <mutex.h>
#include <spinlock.h>
#include <vfs_super_block.h>

KernelStatus vfs_init();

SuperBlock *vfs_mount(const char *name, FileSystemType type, void *data);

#endif // __KERNEL_VFS_H__
