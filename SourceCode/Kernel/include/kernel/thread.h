//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_THREAD_H__
#define __KERNEL_THREAD_H__

#include "arm/cpu.h"
#include "arm/vmm.h"
#include "kernel/kheap.h"
#include "kernel/kobject.h"
#include "kernel/kqueue.h"
#include "kernel/kstack.h"
#include "kernel/list.h"
#include "kernel/rbtree.h"
#include "kernel/vfs_dentry.h"
#include "libc/stdint.h"

typedef uint32_t CpuNum;
typedef uint32_t CpuMask;
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

typedef enum CloneFlags {
    CLONE_VM = 0x1,
    CLONE_FS = 0x1 << 1,
    CLONE_FILES = 0x1 << 2,
} CloneFlags;

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

typedef struct CpuContextSave {
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t sl;
    uint32_t fp;
    uint32_t sp;
    uint32_t pc;
    uint32_t extra[2];
} CpuContextSave;

typedef uint32_t (*ThreadStartRoutine)(void *arg);

typedef struct SectionInfo {
    uint32_t codeSectionAddr;
    uint32_t codeEndSectionAddr;
    uint32_t roDataSectionAddr;
    uint32_t roDataEndSectionAddr;
    uint32_t dataSectionAddr;
    uint32_t dataEndSectionAddr;
    uint32_t bssSectionAddr;
    uint32_t bssEndSectionAddr;
} SectionInfo;


#define FD_STDIN 0
#define FD_STDOUT 1
#define FD_STDERR 2

typedef struct FileDescriptor {
    uint32_t pos;
    DirectoryEntry *directoryEntry;
    ListNode node;
    KernelObject object;
} FileDescriptor;

typedef uint32_t (*FilesStructOperationOpenFile)(struct FilesStruct *filesStruct,
                                                 struct DirectoryEntry *directoryEntry);

typedef struct FilesStructOperations {
    FilesStructOperationOpenFile openFile;
} FilesStructOperations;

typedef struct FilesStruct {
    KernelVector fileDescriptorTable;
    FilesStructOperations operations;
} FilesStruct;

typedef struct MemoryStructOperations {

} MemoryStructOperations;

typedef struct MemoryStruct {
    VirtualMemory virtualMemory;
    Heap heap;
    SectionInfo sectionInfo;
    MemoryStructOperations operations;
} MemoryStruct;

typedef KernelStatus (*ThreadOperationSuspend)(struct Thread *thread);

typedef KernelStatus (*ThreadOperationResume)(struct Thread *thread);

typedef KernelStatus (*ThreadOperationSleep)(struct Thread *thread, uint32_t deadline);

typedef KernelStatus (*ThreadOperationDetach)(struct Thread *thread);

typedef KernelStatus (*ThreadOperationJoin)(struct Thread *thread, int *returnCode, uint32_t deadline);

typedef KernelStatus (*ThreadOperationExit)(struct Thread *thread, uint32_t returnCode);

typedef KernelStatus (*ThreadOperationKill)(struct Thread *thread);

typedef struct Thread *(*ThreadOperationCopy)(struct Thread *thread, CloneFlags cloneFlags, uint32_t heapStart);

typedef struct ThreadOperations {
    ThreadOperationSuspend suspend;
    ThreadOperationResume resume;
    ThreadOperationSleep sleep;
    ThreadOperationDetach detach;
    ThreadOperationJoin join;
    ThreadOperationExit exit;
    ThreadOperationKill kill;
    ThreadOperationCopy copy;
} ThreadOperations;

typedef struct Thread {
    uint32_t magic;
    CpuContextSave cpuContextSave;

    struct Thread *parentThread;
    uint64_t pid;
    char name[THREAD_NAME_LENGTH];
    KernelStack stack;
    ThreadStartRoutine entry;

    uint32_t flags;
    uint32_t signals;

    ThreadStatus threadStatus;
    ListNode threadList;
    KQueueNode threadReadyQueue;

    uint32_t priority;

    RBNode rbNode;
    uint64_t startTime;
    uint32_t runtimeNs;
    uint32_t runtimeVirtualNs;


    CpuNum lastCpu;
    CpuNum currCpu;
    CpuMask cpuAffinity;

    uint32_t returnCode;

    ThreadOperations operations;

    MemoryStruct memoryStruct;
    FilesStruct filesStruct;

    KernelObject object;

    uint32_t interruptable;
    void *arg;

} Thread;

Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority, RegisterCPSR cpsr);

KernelStatus thread_free(Thread *thread);

Thread *thread_create_idle_thread(uint32_t cpuNum);

KernelStatus thread_reschedule();

#endif//__KERNEL_THREAD_H__
