中文版

目前 SynestiaOs 实现了内核进程，本篇文档介绍 SynestiaOs 中进程的基础设施，包括进程的定义、进程的状态、进程的优先级、进程的



进程的定义如下：

```c
typedef struct Thread {
  uint32_t magic;
  CpuContextSave cpuContextSave;

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

  uint32_t priority;

  RBNode rbTree;
  uint64_t startTime;
  uint32_t runtimeNs;
  uint32_t runtimVirtualNs;

  bool interruptable;

  CpuNum lastCpu;
  CpuNum currCpu;
  CpuMask cpuAffinity;
  void *arg;

  uint32_t returnCode;
} __attribute__((packed)) Thread;
```

- magic为每一个进程的魔数，用于调试，关于魔数字，有一个宏定义了 `#define THREAD_MAGIC (0x74687264)`，是ASCII码，转换过来就是`THRE`。
- cpuContextSave 是 CpuContextSave 类型的结构体，目前没有使用。
- pid：进程的ID
- name：进程的名字
- stack：进程栈，内核进程的栈位于内核空间中，用户态的栈位于用户空间中，只是分配的基址不一样，结构是一样的。
- 

