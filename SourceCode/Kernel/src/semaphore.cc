//
// Created by XingfengYang on 2020/7/17.
//

#include <log.h>
#include <sempahore.h>
#include <stdbool.h>
#include <thread.h>

extern Thread *currentThread;

void semaphore_default_post(Semaphore *semaphore) {}

void semaphore_default_wait(Semaphore *semaphore) {}
