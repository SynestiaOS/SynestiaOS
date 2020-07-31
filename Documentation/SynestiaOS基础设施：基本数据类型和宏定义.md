中文版：

本篇文档介绍 SynestiaOS 中定义的基本数据类型和一些宏定义。这些数据类型和宏定义位于`SynestiaOS/SourceCode/Kernel/include/type.h` 、 `SynestiaOS/SourceCode/Libraries/LibC/include/stdint.h` 和 `SynestiaOS/SourceCode/Libraries/LibC/include/stdlib.h` 中。



### 基本数据类型

```c
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed long int32_t;
typedef signed long long int64_t;

typedef _Bool bool;
```



### 一些宏定义

```c
#define DEFAULT_STRING_LEN 256

#define B 1
#define KB 1024 * B
#define MB 1024 * KB
#define GB 1024 * MB

#define BITS_IN_UINT32 32
#define MAX_UINT_32 0xFFFFFFFF

#define nullptr (void *)0
```

在 `SynestiaOS` 中，经常会遇到函数的返回值类型是 `KernelStatus`，该类型定义如下：

```c
typedef enum KernelStatus {
  OK = 0,
  ERROR,
} KernelStatus;
```



