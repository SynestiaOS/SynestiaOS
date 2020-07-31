操作系统中，总会存在竞态条件，竞态条件一旦发生会对系统造成严重的影响，甚至是致命的。所以需要做一些工作来保护代码避免竞态条件。SynestiaOS实现了原子操作、自旋锁、互斥量等。

本篇文档介绍SynestiaOS同步方法中的原子操作，它是其它同步方法的基础，目前SynestiaOS实现了整数的原子操作，还没有实现单独位的原子操作，原子操作的定义位于：`SynestiaOS/SourceCode/Kernel/include/atomic.h` 和 `SynestiaOS/SourceCode/Kernel/src/atomic.c` 中。

在介绍原子操作之前，先来简单介绍下相关的一些术语：

### 临界区、竞态条件和同步

**临界区**就是访问和操作共享数据的代码段，试想，多个执行的线程同时并发的访问同一个资源，例如说共享内存，那么通常情况下是很不安全的，为了避免在临界区中并发访问，就必须保证访问的操作是原子性的。

如果恰巧两个执行的线程处于同一个临界区同时执行，就叫做它们处于**竞态条件 `race conditions`**，也就是出现了线程竞争，虽然出现的概率比较小，但是一旦出现调试会非常困难。

而**同步**的意思就是避免并发和防止竞态条件。



### 可能的造成并发执行的原因

用户空间需要同步，因为用户程序会被调度器无情地抢占和重新调度，那么就有可能出现用户进程正处于临界区，并没有执行完，这个时候调度器就选择了另外一个进程调度上CPU了，也就是出现了非自愿的抢占了，而恰巧新调度上CPU的进程也处于同一个临界区，可以想象的一个场景就是两个进程在操作同一个段共享内存，那么这个时候这两个进程就发生了竞争。

内核中有很多可能造成并发执行的原因：

- 中断：中断几乎可以在任何时刻异步地发生，可以随时打断当前正在执行的代码，而这段代码恰巧是临界区。
- 软中断和tasklet：内核会在任何时刻唤醒或者调度软中断和tasklet，也会随时打断当前正在执行的代码
- 内核抢占：处于内核态的任务会被另一个任务抢占，当然目前SynestiaOS是不允许内核抢占的。
- ······



### 原子变量的定义

关于原子操作，最经典的例子就是加1操作了，在汇编层面，加1操作会分为三个步骤：将计数器的值从内存复制到处理器寄存器中，之后将它的值加1，最后把寄存器中的数据写回到内存。所以如果有另外一个CPU同时也在操作这个内存单元进行加1操作，那么就会导致错误发生。

需要注意的是，原子操作是解决多个CPU在操作同一个内存单元时的情景，是面向多核cpu的，如果是单核心cpu系统，那么原子变量和普通变量是一样的，因为没有其它处理器的干扰了。另外原子操作最常见的例子就是实现计数器。

```c
typedef struct Atomic {
  volatile uint32_t counter;
} Atomic;
```

- 可以看到原子变量的定义就是一个地址，因为原子变量也是变量，一个变量就是一个内存单元中的内容，一个内存单元就使用一个地址来访问了。
- 没有直接采用c语言中的数据类型例如 `u32` 的原因是让原子函数只接收 `Atomic`类型的操作数，可以强制原子操作只和这种数据类型一起使用，同时也防止原子类型的变量被视作普通变量进行加减操作。 

创建一个原子变量的方法如下：

```c
Atomic *lock;
atomic_create(lock);


void atomic_create(Atomic *atomic) { atomic_set(atomic, 0); }
```

- 它使用 `atomic_set` 方法，如下



### 给原子变量置值

那么如何给原子变量设置为某个值，这个操作其实可以通过 `*((atoimc)->counter) = (i)` 来进行，因为这条语句的操作本身就是原子性的，但是原子操作的加减中需要涉及到底层的体系结构，在SynestiaOS中，涉及的就是ARM底层的汇编指令了。所以为了统一，SynestiaOS也实现了汇编层面的给原子变量置值的操作：

```c
/**
 * Because reading and writing directly to the memory address does not go through the register,
 * it is also atomic to directly manipulate the memory address.
 * So you can also use (*((atoimc)->counter) = (i))
 */
void atomic_set(Atomic *atomic, uint32_t val) {
  volatile uint32_t tmp;
  __asm__ __volatile__("@ atomic_set\n\t"
                       "1:  ldrex    %0, [%1]\n\t"          //ldrex : arm的
                       "    strex    %0, %2, [%1]\n\t"      //strex
                       "    teq      %0, #0\n\t"
                       "    bne      1b"
                       : "=&r"(tmp)
                       : "r"(&atomic->counter), "r"(val)
                       : "cc");
}
```

- 第一个传入的参数就是要设置的原子变量，第二个传入的参数就是要设置的值是多少。
- 在该函数中主要进行内联汇编操作

这里要借助 `ARM` 体系的 `LL` 和 `SC` 操作，也就是 `Load-Link` 和 `store-conditional` 操作，LL操作用来返回一个内存单元上的值，而SC操作就是向一个内存单元写入一个值，但是只有在LL开始到SC的时候都没有发生改变的时候，写入才会成功，所以ARM硬件提供的LL和SC操作，是SynestiaOS实现原子操作的基础。



### LDREX和STREX

ARM中的 `LL` 和 `SC` 语句是使用 `ldrex` 和 `strex` 实现的：

```
LDREX Rx, [Ry]
```

- 用来读取 Ry 寄存器指向的内存单元，并保存到 `Rx` 寄存器当中，同时把Ry指向的内存区域标记为独占访问

```
STREX Rx, Ry, [Rz]
```

- strex在更新内存的时候，会检查这段内存是不是被标记了独占访问，如果被标记了独占访问，就把Ry中指向的值更新到Rz指向的内存，并把Rx设置成0，如果strex设置成功会d则会清除独占访问的标志。

所以说这两条指令是原子操作的基础。ARM本身还会有复杂的逻辑运行，可以移步[这里](https://blog.csdn.net/Roland_Sun/article/details/47670099)。



### 读取原子变量

```c
/**
 * Because reading and writing directly to the memory address does not go through the register,
 * it is also atomic to directly manipulate the memory address.
 * So you can also use (*(volatile int *)&(atomic)->counter)
 */
uint32_t atomic_get(Atomic *atomic) {
  volatile uint32_t result;
  __asm__ __volatile__("@ atomic_get\n\t"
                       "	ldrex	%0, [%1]"
                       : "=&r"(result)
                       : "r"(&atomic->counter));
  return result;
}
```

- 获取原子变量的值也可以通过 `(*(volatile int *)&(atomic)->counter)` 实现，因为内存读取也是原子操作，不经过寄存器，所以也是为了统一，实现了汇编层面的 `atomic_get`。

- 读取原子变量使用的是上面介绍的 `ldrex` 指令。



### 原子变量加法减法操作

```c
uint32_t atomic_add(Atomic *atomic, uint32_t val) {
  volatile uint32_t tmp;
  uint32_t result;
  __asm__ __volatile__("@ atomic_add\n\t"
                       "1:  ldrex    %0, [%2]\n\t"
                       "    add      %1, %0, %3\n\t"
                       "    strex    %0, %1, [%2]\n\t"
                       "    teq      %0, #0\n\t"
                       "    bne      1b"
                       : "=&r"(tmp), "=&r"(result)
                       : "r"(&atomic->counter), "r"(val)
                       : "cc");
  return result;
}
```

- 原子变量的加法减法操作区别于原子变量的置值，加法操作必须经过寄存器，所以必须在汇编层面操作，类似于给原子变量置值，加法操作会在 `ldrex` 和 `strex` 之间进行add操作。
- 原子变量的减法操作就对应使用sub指令了：

```c
uint32_t atomic_sub(Atomic *atomic, uint32_t val) {
  volatile uint32_t tmp;
  uint32_t result;
  __asm__ __volatile__("@ atomic_sub\n\t"
                       "1:  ldrex    %0, [%2]\n\t"
                       "    sub      %1, %0, %3\n\t"
                       "    strex    %0, %1, [%2]\n\t"
                       "    teq      %0, #0\n\t"
                       "    bne      1b"
                       : "=&r"(tmp), "=&r"(result)
                       : "r"(&atomic->counter), "r"(val)
                       : "cc");
  return result;
}
```



### 原子变量的加1减1操作

回到文档开始的经典例子，原子变量一个经常遇到的应用场景就是加1减1操作了，所以SynestiaOS中，实现了原子变量的加1减1操作：

```c
uint32_t atomic_inc(Atomic *atomic) { return atomic_add(atomic, 1); }

uint32_t atomic_dec(Atomic *atomic) { return atomic_sub(atomic, 1); }
```

- 代码其实就是调用了 `atomic_add` 和 `atomic_sub` 函数。