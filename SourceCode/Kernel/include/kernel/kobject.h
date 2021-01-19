//
// Created by XingfengYang on 2020/11/22.
//

#ifndef __SYNESTIAOS_KOBJECT_H__
#define __SYNESTIAOS_KOBJECT_H__

#include "kernel/list.h"
#include "libc/stdint.h"

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

typedef uint32_t (*KernelObjectOperationGetSize)(struct KernelObject *object);

typedef struct KernelObjectOperations {
    KernelObjectOperationGetObject getObject;
    KernelObjectOperationGetSize size;
} KernelObjectOperations;

typedef struct KernelObject {
    KernelObjectType type;
    KernelObjectStatus status;
    struct ListNode list;
    KernelObjectOperations operations;
} KernelObject;

KernelObject* kobject_create(KernelObject* kObject);

#endif//__SYNESTIAOS_KOBJECT_H__
