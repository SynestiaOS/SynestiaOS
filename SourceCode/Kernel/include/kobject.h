//
// Created by XingfengYang on 2020/11/22.
//

#ifndef __SYNESTIAOS_KOBJECT_H__
#define __SYNESTIAOS_KOBJECT_H__

#include <stdint.h>

typedef enum KernelObjectType{
    THREAD,
    MUTEX,
    SEMAPHORE,
    FILE_DESCRIPTOR,
} KernelObjectType;


typedef enum KernelObjectStatus{
    USING,
    FREE,
} KernelObjectStatus;

typedef struct KernelObject{
    KernelObjectType type;
    KernelObjectStatus status;
    struct KernelObject* next;
} KernelObject;

#endif //__SYNESTIAOS_KOBJECT_H__
