#ifndef __KERNEL_RINGBUFFER_H__
#define __KERNEL_RINGBUFFER_H__

#include <list.h>
#include <stdint.h>
#include <type.h>

typedef ListNode KQueue;

KernelStatus kqueue_enqueue(KQueue *queue, KQueue *node);

KQueue *kqueue_dequeue(KQueue *queue);

uint32_t kqueue_size(KQueue *queue);

#endif// __KERNEL_RINGBUFFER_H__
