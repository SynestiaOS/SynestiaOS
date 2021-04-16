#ifndef SYNESTIAOS_CAPABILITY_NODE_H
#define SYNESTIAOS_CAPABILITY_NODE_H

#include "kernel/stdint.h"

// 2-8-8-12
typedef struct DirMap {
    uint32_t nums[4];
    uint32_t slot[4];
    uint32_t freelist[4];
} DirMap;

typedef struct CapabilityNode {
    DirMap ownTable; // Own ability and authority
    DirMap conferTable; // Capabilities and permissions granted to other threads
    DirMap acquireTable; // Ability and authority acquired
} CapabilityNode;

#endif // SYNESTIAOS_CAPABILITY_H