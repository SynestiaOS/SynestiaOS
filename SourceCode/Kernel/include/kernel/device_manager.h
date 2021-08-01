//
// Created by XingfengYang on 2021/7/31.
//
#ifndef SYNESTIAOS_DEVICE_MANAGER_H
#define SYNESTIAOS_DEVICE_MANAGER_H

#include "kernel/type.h"
#include "kernel/list.h"
#include "libc/stdint.h"
#include "kernel/device.h"
#include "device_tree/dtb.h"

typedef uint32_t (*DeviceProbe)(struct DeviceDescription *desc, DeviceTreeNode *node);

typedef struct DeviceDescription {
        const char* compatible;
        DeviceProbe probe;
        DeviceProbe _probe;
} DeviceDescription;

typedef uint32_t (*DeviceManagerOperationDoProbe)(DeviceDescription *desc);

typedef struct DeviceManagerOperations {
        Device* deviceHead;
        DeviceManagerOperationDoProbe do_probe;
} DeviceManagerOperations;

typedef struct DeviceManager {
       DeviceManagerOperations ops;
} DeviceManager;

#endif // SYNESTIAOS_DEVICE_MANAGER_H