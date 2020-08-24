//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_THREAD_H__
#define __KERNEL_THREAD_H__

#include <kqueue.h>
#include <kstack.h>
#include <list.h>
#include <rbtree.h>
#include <stdint.h>
#include <vfs_dentry.h>

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

typedef enum CloneFlags {
  CLONE_VM = 0x1,
  CLONE_FS = 0x1 << 1,
  CLONE_FILES = 0x1 << 2,
} CloneFlags;

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
} __attribute__((packed)) CpuContextSave;

typedef uint32_t (*ThreadStartRoutine)(void *arg);

typedef struct VMMAssociatedSpace {
  uint32_t pageTableAddr;
  uint32_t codeSectionAddr;
  uint32_t roDataSectionAddr;
  uint32_t dataSectionAddr;
  uint32_t bssSectionAddr;
} __attribute__((packed)) VMMAssociatedSpace;

typedef struct FileDescriptor {
  uint32_t pos;
  DirectoryEntry *directoryEntry;
  ListNode node;
} FileDescriptor;

typedef uint32_t (*FilesStructOperationOpenFile)(struct FilesStruct *filesStruct,
                                                 struct DirectoryEntry *directoryEntry);

typedef struct FilesStructOperations {
  FilesStructOperationOpenFile openFile;
} FilesStructOperations;

typedef struct FilesStruct {
  KernelVector *fileDescriptorTable;
  FilesStructOperations operations;
} FilesStruct;

typedef struct MemoryStructOperations {

} MemoryStructOperations;
typedef struct MemoryStruct {
  VMMAssociatedSpace vmmSpace;
  MemoryStructOperations operations;
} MemoryStruct;

typedef KernelStatus (*ThreadOperationSuspend)(struct Thread *thread);

typedef KernelStatus (*ThreadOperationResume)(struct Thread *thread);

typedef KernelStatus (*ThreadOperationSleep)(struct Thread *thread, uint32_t deadline);

typedef KernelStatus (*ThreadOperationDetach)(struct Thread *thread);

typedef KernelStatus (*ThreadOperationJoin)(struct Thread *thread, int *returnCode, uint32_t deadline);

typedef KernelStatus (*ThreadOperationExit)(struct Thread *thread, uint32_t returnCode);

typedef KernelStatus (*ThreadOperationKill)(struct Thread *thread);

typedef struct Thread *(*ThreadOperationClone)(struct Thread *thread, CloneFlags cloneFlags, uint32_t heapStart);

typedef struct ThreadOperations {
  ThreadOperationSuspend suspend;
  ThreadOperationResume resume;
  ThreadOperationSleep sleep;
  ThreadOperationDetach detach;
  ThreadOperationJoin join;
  ThreadOperationExit exit;
  ThreadOperationKill kill;
  ThreadOperationClone clone;
} ThreadOperations;

typedef struct Thread {
  uint32_t magic;
  CpuContextSave cpuContextSave;

  struct Thread *parentThread;
  uint64_t pid;
  char name[THREAD_NAME_LENGTH];
  KernelStack *stack;
  ThreadStartRoutine entry;

  uint32_t flags;
  uint32_t signals;

  ThreadStatus threadStatus;
  ListNode threadList;
  KQueue threadReadyQueue;

  uint32_t priority;

  RBNode rbNode;
  uint64_t startTime;
  uint32_t runtimeNs;
  uint32_t runtimVirtualNs;

  bool interruptable;

  CpuNum lastCpu;
  CpuNum currCpu;
  CpuMask cpuAffinity;
  void *arg;

  uint32_t returnCode;

  ThreadOperations operations;

  MemoryStruct memoryStruct;
  FilesStruct filesStruct;

} __attribute__((packed)) Thread;

Thread *thread_create(const char *name, ThreadStartRoutine entry, void *arg, uint32_t priority);

Thread *thread_create_idle_thread(uint32_t cpuNum);

KernelStatus thread_reschedule();

#endif //__KERNEL_THREAD_H__
