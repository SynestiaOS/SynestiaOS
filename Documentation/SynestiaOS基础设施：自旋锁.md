临界区理想的情况是每一个临界区的代码都能是变量加减操作，但是现实总是残酷的，在代码逻辑中经常会遇到复杂的情景，例如队列的入队和出队，在入队和出队的同时，可能还会伴随着一些逻辑操作，这个时候原子操作就无能为力了，就需要使用较为复杂的锁机制。

本篇文档介绍SynestiaOS的处理竞态的另一种方式，也就是另一种同步方法自旋锁`spin lock`，自旋锁则面向多个线程设置，用于保护短的代码段，所以会很快执行完毕，自旋锁存在于SynestiaOS中各个数据结构中，可以说大多数的数据结构都需要使用自旋锁，在处理某些关键的成员的时候，必须获得相应的自旋锁。

锁的使用是自愿的，不是强制性的，使用锁的原因完全是因为避免竞态条件，因为锁是采用原子操作实现的，而原子操作是不存在竞争的。需要注意的是，在编写代码的时候，能使用原子操作的时候，就尽量使用原子操作，不使用复杂的锁机制，因为原子操作带来的开销会小，对`cache-line` 的影响也会小。

自旋锁的定义位于：`SynestiaOS/SourceCode/Kernel/include/spinlock.h` 和 `SynestiaOS/SourceCode/Kernel/src/spinlock.c` 中。



### 自旋锁的定义

```c
typedef struct SpinLock {
  Atomic *lock;
} SpinLock;
```

- 自旋锁最多只能被一个可执行的线程持有，如果一个线程尝试去获取一个已经被持有的自旋锁，那么这个线程就会一直进行进行忙循环，直到等待到锁重新可用。一个例子就是两个人想要同时去同一个卫生间的同一个坑位，但是一个坑位只能允许一个人进入，另一个人就需要等待，直到里面的人出来。
- 另外需要注意一个事情，那就是自旋锁不应该被长期占有，因为等待的线程此时什么也不干，只是在等待，可以想象一下在坑位门口等待着的人那种焦虑的心情。当然等待自旋锁的线程可以进入睡眠然后等到锁重新可用的时候在唤醒它，这样就不必等待，CPU也可以处理其他事情，但是这明显会带来两次进程的切换，也就是两 次 `context_switch()`，这又是一个比较大的开销，所以我们尽量保证临界区的代码执行时间小于两次 `context_switch()` 的时间，但是这个时间我们又无法估计，所以使用自旋锁时就遵循自旋锁的初心，只保护尽量短的代码段。
- 目前SynestiaOS的自旋锁是通过原子变量实现的



### 自旋锁的使用

自旋锁的基本使用方法如下：

```c
SpinLock *lock;
spinlock_create(lock);

void spinlock_create(SpinLock *spinLock, Atomic *atomic) { atomic_create(atomic); }
```

- 实际上就是要初始化 `SpinLock` 中的原子变量。
- 注意该处代码尚不完善，后续会进行改进。

创建好之后就可以使用自旋锁来保护临界区了：

```c
spinlock_acquire(lock);
/*临界区*/
spinlock_release(lock);
```

- 如果内核中其它地方还没有获得锁，那么就由当前的CPU获取，其它的处理器不会再进入自旋锁保护的区域
- 如果自旋锁已经被其他的CPU获取了，那么spinlock_acquire会进入一个等待，重复检查自旋锁是否已经被释放。等待可以获取锁的时候，再进入临界区。
- 如果内核不支持抢占，而且是单核CPU的系统，那么就不会出现几个CPU同时进入临界区的情况，但是如果单核心CPU支持内核抢占，这种情况和两个处理器同时在临界区执行的情况是等效的。SynestiaOS目前不支持内核抢占，所以我们面对的是多CPU的情景。



### 获得Spin lock

```c
void spinlock_acquire(SpinLock *spinLock) {
  if (atomic_get(spinLock->lock) == 0) {
    atomic_set(spinLock->lock, 1);
  } else {
    asm volatile("WFE");
  }
}
```

- 由于自旋锁是通过原子变量实现的，所以实际的操作就是操作原子变量了。

- 获得锁的过程是检测当前spinlock的原子变量是否为0，0代表没有线程获得锁，而1代表已经被别的线程获得了锁，

  如果没有人获得锁，那么当前CPU就会把这个自旋锁的原子变量加1，表示我拿到了锁；而如果检测到别的线程已经获得了锁，那么就会执行 `WFE` 指令。

- WFE是ARM架构的指令，执行 `WFE` 指令后，根据 `Event Register` 的状态，有两种情况：如果Event Register为1，该指令会把它清零，然后执行完成（不会standby）；如果Event Register为0，和WFI类似，进入low-power standby state，直到有 `WFE Wakeup events` 发生。所以前文所说的让等待的线程一直循环等待检测锁是否释放的操作就可以使用WFE指令优化，让该CPU进入standby模式，还可以节省功耗。



### 释放Spin lock

```c
void spinlock_release(SpinLock *spinLock) {
  atomic_set(spinLock->lock, 0);
  asm volatile("SEV");
}
```

- 释放锁的操作相对简单，就是把自旋锁的原子变量设置成0即可。
- 最重要的是要执行下面的SEV指令，所谓的SEV指令，就是一个用来改变 `Event Register` 的指令，`WFE` 可以被任何 `PE(process element)` 上执行的 `SEV`指令唤醒。这就是spinlock实现的关键，如果别的CPU核在等待自旋锁，说明它已经执行了 `WFE` 指令，进入了standby模式，那么这个时候如果其它的PE执行了 `SEV` 指令，就会唤醒它，从而继续运行。
- 需要注意使用了自旋锁以后，一定要记得释放锁，如果获得了锁以后不释放，其它的线程迟早会进入临界区，就会进入无限循环的状态，或者CPU进入无限 `standby` 模式，就会产生死锁。