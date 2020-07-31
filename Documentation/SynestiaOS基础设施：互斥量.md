互斥信号量mutex是一种特殊的信号量，它的实现是在信号量的基础上做出了一些限制，mutex在某一时刻只允许有一个持有者，count的值只能是0或者1，1代表资源不可用，而0代表可用。互斥信号量使用的情景比计数信号量的情景要多。

信号量的定义位于：`SynestiaOS/SourceCode/Kernel/include/mutex.h` 和 `SynestiaOS/SourceCode/Kernel/src/mutex.c` 中。



### mutex的定义

```c
typedef struct Mutex {
  Atomic *val;
  KQueue *waitQueue;
} Mutex;
```

- mutex定义和信号量的定义相同，只不过 `count` 改成了 `Val`。只是在操作上加以限制，类似于链表和栈的关系。



### 创建mutex

```c
void mutex_create(Mutex *mutex, Atomic *atomic) {
  mutex->val = atomic;
  mutex->waitQueue = nullptr;
  atomic_create(atomic);
}
```

- 这里不需要强制原子变量 Val 的大小是1，因为在mutex的操作中会解决大小问题。



### 获取mutex

```c
bool mutex_acquire(Mutex *mutex) {
  if (atomic_get(mutex->val) == 0) {
    atomic_set(mutex->val, 1);
    return true;
  } else {
    // can not get the lock, just add to lock wait list
    KernelStatus enQueueStatus = kqueue_enqueue(mutex->waitQueue, &currentThread->threadReadyQueue);
    if (enQueueStatus != OK) {
      LogError("[Mutex]: thread add to wait list failed. \n");
      return false;
    }

    // reomve from schd list
    KernelStatus removeStatus = schd_remove_from_schduler(currentThread);
    if (removeStatus != OK) {
      LogError("[Mutex]: thread remove from schd list failed. \n");
      return false;
    }

    // 2. switch to the next thread in scheduler
    KernelStatus thradSwitchNextStatus = schd_switch_next();
    if (thradSwitchNextStatus != OK) {
      LogError("[Mutex]: thread switch to next failed. \n");
    }
    return false;
  }
}
```

- 如果检测到mutex的Val属性不等于0，就代表有人拿到mutex，此时当前线程就需要被调度下CPU，和信号量操作类似，会进行添加到等待队列，移除出运行队列，切换到下一个线程等操作。
- 如果检测到mutex的Val属性等于0，说明锁没有被占有，此时设置Val字段为1，代表mutex已经被占有。



### 释放mutex

```c
void mutex_release(Mutex *mutex) {
  atomic_set(mutex->val, 0);
  KQueue *queueNode = kqueue_dequeue(mutex->waitQueue);
  Thread *releasedThread = getNode(queueNode, Thread, threadReadyQueue);
  KernelStatus addToSchduler = schd_add_to_schduler(releasedThread);
  if (addToSchduler != OK) {
    LogError("[Mutex]: thread add to schduler failed. \n");
  }
}
```

- 释放mutex，首先将Val的值设置为0，代表mutex现在没有被使用，也就是释放了mutex。
- 之后和信号量类似，会进行移除出等待队列，得到线程描述符起始地址，添加进运行队列等操作。