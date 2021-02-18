#ifndef SYNESTIAOS_HEAP_DEBUG_H
#define SYNESTIAOS_HEAP_DEBUG_H

#include "libc/stdint.h"

void heap_test();

void dump_kernel_heap(uint32_t type, const char *extend_info);

typedef enum HeapDumpType {
    GET_HEAP_STAT = 0x1,
    GET_USING_LIST = 0x1 << 1,
    GET_FREE_LIST = 0x1 << 2,
    GET_PHYSICAL_PAGE = 0x1 << 3,
    GET_USER_SPACE_PAGE = 0x1 << 4,
} HeapDumpType;

#endif //SYNESTIAOS_HEAP_DEBUG_H
