//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_SEMPHORE_H__
#define __KERNEL_SEMPHORE_H__
#include <atomic.h>
#include <kqueue.h>
#include <stdint.h>

typedef struct Semphore {
  Atomic *count;
  KQueue *waitQueue;
} Semphore;

void semphore_create(Semphore *semphore, Atomic *atomic, uint32_t count);

uint32_t semphore_post(Semphore *semphore);

KernelStatus semphore_wait(Semphore *semphore);

#endif // __KERNEL_SEMPHORE_H__
