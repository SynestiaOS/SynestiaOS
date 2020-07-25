//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_TYPE_H__
#define __KERNEL_TYPE_H__

#define B 1
#define KB 1024 * B
#define MB 1024 * KB
#define GB 1024 * MB

#define BITS_IN_UINT32 32
#define MAX_UINT_32 0xFFFFFFFF

#define nullptr (void *)0
#define readonly const

typedef int (*funcPtr)(void);

typedef enum KernelStatus {
  OK = 0,
  ERROR,
} KernelStatus;

#endif //__KERNEL_TYPE_H__
