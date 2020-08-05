//
// Created by XingfengYang on 2020/7/17.
//

#include <kqueue.h>
#include <log.h>
#include <mutex.h>
#include <stdbool.h>
#include <thread.h>

extern Thread *currentThread;

void mutex_default_acquire(struct Mutex *mutex) {
  if (atomic_get(&mutex->val) == 0) {
    atomic_set(&mutex->val, 1);
    return true;
  } else {
    // can not get the lock, just add to lock wait list

    // reomve from schd list

    // 2. switch to the next thread in scheduler
  }
}

void mutex_default_release(struct Mutex *mutex) {}
