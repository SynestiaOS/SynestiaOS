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
#define THREAD_NAME_LENGTH 32

typedef uint32_t VirtualAddress;

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
    VirtualAddress base;
    uint32_t size;
    VirtualAddress top;
    void *virtualMemoryAddress;
} __attribute__((packed)) KernelStack;

typedef struct ThreadStartRoutine {

} __attribute__((packed)) ThreadStartRoutine;

typedef struct VMMAssociatedSpace {

} __attribute__((packed)) VMMAssociatedSpace;

typedef struct Thread {
    uint32_t magic;
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

    char name[THREAD_NAME_LENGTH];
    uint32_t returnCode;

} __attribute__((packed)) Thread;


Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority);

void init_thread_struct(Thread *thread, const char *name);

void thread_exit(uint32_t returnCode);

void thread_kill(Thread *thread);

#endif //__KERNEL_THREAD_H__
