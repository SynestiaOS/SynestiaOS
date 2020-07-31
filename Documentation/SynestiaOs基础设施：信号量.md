本篇文档介绍SynestiaOS实现的信号量Semaphore， 这里的信号量指的是SynestiaOS内核态使用的信号量，它和用户空间的信号有所不同。自旋锁适用于临界区比较短的情景，所以不会使得线程进入睡眠状态，那么信号量就是来解决临界区比较长的情景，所以信号量会使线程进入睡眠。那么由于会使进程进入睡眠状态，所以只能在进程上下文中获得信号量，因为中断上下文是不能进行调度的。另外一个就是占用信号量的时候补鞥呢再占用自旋锁了，因为线程会进入睡眠。

信号量分为计数信号量和二值信号量。回顾自旋锁的文档，自旋锁在某一个时刻只能允许一个线程持有，而信号量则没有要求这一点，它允许信号量同时持有的数量在定义信号量的时候可以指定，所以，信号量就需要一个属性来记录这个数量`count`，这个时候的信号量就叫做计数信号量，也就是允许多个线程同时访问临界区，听起来就会发生竞争，所以在内核中使用到它的情况并不多，但是对特定的代码是很有用的。

而我们一般想到的同一个时刻仅允许有一个信号量的持有者的情况下，就叫做二值信号量，也就是 `mutex` 了，这个放到`mutex` 文档中介绍。

信号量的定义位于：`SynestiaOS/SourceCode/Kernel/include/semphore.h` 和 `SynestiaOS/SourceCode/Kernel/src/semphore.c` 中。



### 信号量的定义

```c
typedef struct Semphore {
  Atomic *count;
  KQueue *waitQueue;
} Semphore;
```

- count代表可用的资源个数，由于有可能多个进程同时操作count属性，而且是进行加减操作，所以需要使用原子变量。
- waitQueue是当前信号量的等待队列，如果资源为-1就代表有一个线程在等待信号量。



### 信号量的创建

```c
void semphore_create(Semphore *semphore, Atomic *atomic, uint32_t count) {
  semphore->count = atomic;
  semphore->waitQueue = nullptr;
  atomic_set(atomic, count);
}
```

- 传入的参数是一个信号量，一个原子变量，还有资源的个数；
- 信号量的创建如上，进行字段的赋值。



### 信号量的DOWN操作

```c
KernelStatus semphore_wait(Semphore *semphore) {
  if (atomic_get(semphore->count) > 0) {
    atomic_dec(semphore->count);
    return OK;
  } else {
    // can not get the lock, just add to lock wait list
    KernelStatus enQueueStatus = kqueue_enqueue(semphore->waitQueue, &currentThread->threadReadyQueue);
    if (enQueueStatus != OK) {
      LogError("[Semphore]: thread add to wait list failed. \n");
      return ERROR;
    }
    // reomve from schd list
    KernelStatus removeStatus = schd_remove_from_schduler(currentThread);
    if (removeStatus != OK) {
      LogError("[Semphore]: thread remove from schd list failed. \n");
      return ERROR;
    }

    // 2. switch to the next thread in scheduler
    KernelStatus thradSwitchNextStatus = schd_switch_next();
    if (thradSwitchNextStatus != OK) {
      LogError("[Semphore]: thread switch to next failed. \n");
      return ERROR;
    }
    return OK;
  }
}
```

- 该函数为SymestiaOS提供的内核API，用于信号量的sown操作，用于申请信号量。
- 首先会判断当前想要获得的信号量中的资源个数，如果资源个数大于0，代表有资源可用，就把count变量减1，之后返回
- 如果count的大小小于或者等于0了，代表没有资源可用了，这个时候就要把当前线程放入等待队列中，并把该线程从调度队列中移除，这里就会带来一次上下文切换的开销。
- 当前进程被切换下CPU之后，就需要选择另一个线程来调度上CPU，这里就调用 `schd_switch_next()`，之后返回



### 信号量的UP操作

```c
uint32_t semphore_post(Semphore *semphore) {
  atomic_inc(semphore->count);
  KQueue *queueNode = kqueue_dequeue(semphore->waitQueue);
  Thread *releasedThread = getNode(queueNode, Thread, threadReadyQueue);
  KernelStatus addToSchduler = schd_add_to_schduler(releasedThread);
  if (addToSchduler != OK) {
    LogError("[Semphore]: thread add to schduler failed. \n");
  }
  return atomic_get(semphore->count);
}
```

- 该函数为SymestiaOS提供的内核API，用于信号量的up操作，用于释放信号量。
- 执行up操作的时候首先对原子变量执行加1操作，代表释放了资源
- 之后从等待队列里取出第一个线程，注意线程进入等待队列中是通过每一个线程的 `KQueue threadReadyQueue;` 字段管理的，所以拿出来的是 `KQueue threadReadyQueue;`，需要通过 `getNode` 拿到 `Thread` 的首地址，之后再将线程添加到调度队列中去。
- 返回值会返回资源个数