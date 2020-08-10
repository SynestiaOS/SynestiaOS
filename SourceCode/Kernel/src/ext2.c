//
// Created by XingfengYang on 2020/8/7.
//

#include <ext2.h>
#include <log.h>
#include <stdint.h>

extern char _binary_initrd_img_start[];
extern char _binary_initrd_img_end[];
extern char _binary_initrd_img_size[];

KernelStatus ext2_init() {
  Ext2SuperBlock *ext2SuperBlock = (Ext2SuperBlock *)(_binary_initrd_img_start + 1024);
  LogInfo("[Ext2]: Total number of inodes in file system", ext2SuperBlock->indexNodeNums);
}
