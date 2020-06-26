//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_THREAD_H__
#define __KERNEL_THREAD_H__

#include <stdint.h>
#include <list.h>

typedef uint8_t CpuNum;
typedef uint8_t CpuMask;
#define INVALID_CPU 255

typedef enum ThreadStatus {
    THREAD_INITIAL = 0,
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_BLOCKED,
    THREAD_BLOCKED_READ_LOCK,
    THREAD_SLEEPING,
    THREAD_SUSPENDED,
    THREAD_DEATH,
} ThreadStatus;

typedef struct KernelStack {

} KernelStack __attribute__((packed));

typedef struct ThreadStartRoutine {

} ThreadStartRoutine __attribute__((packed));

typedef struct VMMAssociatedSpace {

} VMMAssociatedSpace __attribute__((packed));

typedef struct Thread {
    uint64_t pid;
    List threadList;
    ThreadStatus threadStatus;
    KernelStack stack;
    ThreadStartRoutine entry;
    VMMAssociatedSpace vmmSpace;
    uint32_t flags;
    uint32_t signals;
    List waitQueue;

    uint32_t priority;
    bool interruptable;

    CpuNum lastCpu;
    CpuNum currCpu;
    CpuMask cpuAffinity;
    void *arg;
    uint32_t returnCode;

} Thread __attribute__((packed));


Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority);

void init_thread_struct(Thread *thread, const char *name);

void thread_exit(uint32_t returnCode);

void thread_kill(Thread *thread);

#endif //__KERNEL_THREAD_H__
