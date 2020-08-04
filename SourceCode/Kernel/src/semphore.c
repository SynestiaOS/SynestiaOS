//
// Created by XingfengYang on 2020/7/17.
//

#include <log.h>
#include <semphore.h>
#include <stdbool.h>
#include <thread.h>

extern Thread *currentThread;

void semphore_create(Semphore *semphore, Atomic *atomic, uint32_t count) {
  semphore->count = atomic;
  semphore->waitQueue = nullptr;
  atomic_set(atomic, count);
}

uint32_t semphore_post(Semphore *semphore) {
  atomic_inc(semphore->count);

  return atomic_get(semphore->count);
}

KernelStatus semphore_wait(Semphore *semphore) {
  if (atomic_get(semphore->count) > 0) {
    atomic_dec(semphore->count);
    return OK;
  } else {
    // can not get the lock, just add to lock wait list

    // reomve from schd list

    // 2. switch to the next thread in scheduler
  }
}