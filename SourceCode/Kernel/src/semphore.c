//
// Created by XingfengYang on 2020/7/17.
//

#include <semphore.h>
#include <stdbool.h>
#include <thread.h>

void semphore_create(Semphore *semphore, Atomic *atomic) {
  semphore->count = atomic;
  semphore->waitQueue = nullptr;
  atomic_create(atomic);
}

uint32_t semphore_post(Semphore *semphore) {}

void semphore_wait(Semphore *semphore) {}