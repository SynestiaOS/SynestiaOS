//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_THREAD_H__
#define __KERNEL_THREAD_H__

#include <stdint.h>
#include <list.h>
#include <kstack.h>

typedef uint8_t CpuNum;
typedef uint8_t CpuMask;
#define THREAD_NAME_LENGTH 32
#define THREAD_MAGIC (0x74687264)

#define NUM_PRIORITIES (32)
#define LOWEST_PRIORITY (0)
#define HIGHEST_PRIORITY (NUM_PRIORITIES - 1)
#define DPC_PRIORITY (NUM_PRIORITIES - 2)
#define IDLE_PRIORITY LOWEST_PRIORITY
#define LOW_PRIORITY (NUM_PRIORITIES / 4)
#define DEFAULT_PRIORITY (NUM_PRIORITIES / 2)
#define HIGH_PRIORITY ((NUM_PRIORITIES / 4) * 3)


#define INVALID_CPU 255
#define CPU_0 0
#define CPU_1 1
#define CPU_2 2
#define CPU_3 3
#define CPU_4 4
#define CPU_5 5
#define CPU_6 6
#define CPU_7 7
#define CPU_8 8
#define CPU_9 9
#define CPU_10 10
#define CPU_11 11
#define CPU_12 12
#define CPU_13 13
#define CPU_14 14
#define CPU_15 15

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

typedef uint32_t (*ThreadStartRoutine)(void *arg);

typedef struct VMMAssociatedSpace {

} __attribute__((packed)) VMMAssociatedSpace;

typedef struct Thread {
    uint32_t magic;
    uint64_t pid;
    char name[THREAD_NAME_LENGTH];

    KernelStack *stack;
    ThreadStartRoutine entry;
    VMMAssociatedSpace vmmSpace;

    uint32_t flags;
    uint32_t signals;

    ThreadStatus threadStatus;
    List threadList;
    List readyList;
    List waitQueue;

    uint32_t priority;
    bool interruptable;

    CpuNum lastCpu;
    CpuNum currCpu;
    CpuMask cpuAffinity;
    void *arg;

    uint32_t returnCode;

} __attribute__((packed)) Thread;


Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority);

Thread *thread_create_idle_thread(uint32_t cpuNum);

KernelStatus init_thread_struct(Thread *thread, const char *name);

KernelStatus thread_exit(uint32_t returnCode);

KernelStatus thread_kill(Thread *thread);

#endif //__KERNEL_THREAD_H__
