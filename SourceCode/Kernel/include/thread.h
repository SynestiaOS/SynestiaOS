//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_THREAD_H__
#define __KERNEL_THREAD_H__

#include <stdint.h>
#include <list.h>
#include <kstack.h>
#include "kqueue.h"
#include "rbtree.h"

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

typedef enum CPU {
    CPU_0 = 0,
    CPU_1,
    CPU_2,
    CPU_3,
    CPU_4,
    CPU_5,
    CPU_6,
    CPU_7,
    CPU_8,
    CPU_9,
    CPU_10,
    CPU_11,
    CPU_12,
    CPU_13,
    CPU_14,
    CPU_15,
    INVALID_CPU = 255,
} CPU;

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
    ListNode threadList;
    KQueue threadReadyQueue;
    RBNode rbTree;

    uint32_t runtimeNs;
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
