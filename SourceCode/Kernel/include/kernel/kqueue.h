#ifndef __KERNEL_RINGBUFFER_H__
#define __KERNEL_RINGBUFFER_H__

#include "kernel/list.h"
#include "kernel/type.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"

typedef ListNode KQueueNode;

typedef KernelStatus (*KernelQueueOperationEnQueue)(struct KernelQueue *queue, KQueueNode *node);

typedef KQueueNode *(*KernelQueueOperationDnQueue)(struct KernelQueue *queue);

typedef uint32_t (*KernelQueueOperationSize)(struct KernelQueue *queue);

typedef bool (*KernelQueueOperationIsEmpty)(struct KernelQueue *queue);

typedef struct KernelQueueOperations {
    KernelQueueOperationEnQueue enqueue;
    KernelQueueOperationDnQueue dequeue;
    KernelQueueOperationSize size;
    KernelQueueOperationIsEmpty isEmpty;
} KernelQueueOperations;

typedef struct KernelQueue {
    KQueueNode *head;
    KQueueNode *tail;
    uint32_t size;
    KernelQueueOperations operations;
} KernelQueue;

KernelQueue *kqueue_create(KernelQueue *queue);

KernelStatus kqueue_default_operation_enqueue(struct KernelQueue *queue, KQueueNode *node);

KQueueNode *kqueue_default_operation_dequeue(struct KernelQueue *queue);

uint32_t kqueue_default_operation_size(struct KernelQueue *queue);

bool kqueue_default_operation_is_empty(struct KernelQueue *queue);

#endif// __KERNEL_RINGBUFFER_H__
