//
// Created by XingfengYang on 2020/11/22.
//

#ifndef __SYNESTIAOS_KOBJECT_H__
#define __SYNESTIAOS_KOBJECT_H__

#include "libc/stdint.h"
#include "kernel/list.h"

typedef enum KernelObjectType {
    KERNEL_OBJECT_THREAD = 0,
    KERNEL_OBJECT_MUTEX,
    KERNEL_OBJECT_SEMAPHORE,
    KERNEL_OBJECT_FILE_DESCRIPTOR,
} KernelObjectType;


typedef enum KernelObjectStatus {
    USING,
    FREE,
} KernelObjectStatus;

typedef void *(*KernelObjectOperationGetObject)(struct KernelObject *object);

typedef void (*KernelObjectOperationInit)(struct KernelObject *object, KernelObjectType type,
                                          KernelObjectStatus status);

typedef uint32_t (*KernelObjectOperationGetSize)(struct KernelObject *object);

typedef struct KernelObjectOperations {
    KernelObjectOperationGetObject getObject;
    KernelObjectOperationInit init;
    KernelObjectOperationGetSize size;
} KernelObjectOperations;

typedef struct KernelObject {
    KernelObjectType type;
    KernelObjectStatus status;
    struct ListNode list;
    KernelObjectOperations operations;
} KernelObject;

#endif//__SYNESTIAOS_KOBJECT_H__
