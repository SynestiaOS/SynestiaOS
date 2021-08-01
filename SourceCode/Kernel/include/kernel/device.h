//
// Created by XingfengYang on 2021/7/25.
//
#ifndef SYNESTIAOS_DEVICE_H
#define SYNESTIAOS_DEVICE_H

#include "kernel/type.h"
#include "kernel/list.h"
#include "libc/stdint.h"

typedef struct Device {
        const char* name;
        uint32_t id;
        ListNode node;
} Device;

void register_device(Device *device);

#endif // SYNESTIAOS_DEVICE_H