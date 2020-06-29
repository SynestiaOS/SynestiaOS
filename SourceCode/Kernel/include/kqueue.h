#ifndef __KERNEL_RINGBUFFER_H__
#define __KERNEL_RINGBUFFER_H__

#include <list.h>
#include <stdint.h>
#include <type.h>

KernelStatus kqueue_enqueue(List *queue, List *node);

List *kqueue_dequeue(List *queue);

uint32_t kqueue_size(List *queue);

#endif // __KERNEL_RINGBUFFER_H__
