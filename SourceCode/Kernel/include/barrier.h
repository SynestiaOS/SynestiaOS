//
// Created by XingfengYang on 2020/7/22.
//

#ifndef __KERNEL_BARRIER_H__
#define __KERNEL_BARRIER_H__

#include <mutex.h>

typedef struct Barrier {
  uint32_t arrivalCounter;
  uint32_t leaveCounter;
  uint32_t flag;
  Mutex lock;
};

#endif // __KERNEL_BARRIER_H__