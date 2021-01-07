//
// Created by XingfengYang on 2021/1/7.
//

#ifndef SYNESTIAOS_BUS_H
#define SYNESTIAOS_BUS_H

#include "libc/stdint.h"


typedef struct ServiceBusOperation {

} ServiceBusOperation;

typedef struct ServiceBus {

} ServiceBus;


typedef struct DriverMessageHeader {
    uint32_t id;
    uint32_t length;
    char *data;
} DriverMessageHeader;

typedef void (*DriverOperationSend)(struct Driver *driver, DriverMessageHeader msgHdr);

typedef void (*DriverOperationOnMessage)(struct Driver *driver, DriverMessageHeader msgHdr);

typedef struct DriverOperation {
    DriverOperationSend send;
    DriverOperationOnMessage onMessage;
} DriverOperation;

typedef struct Driver {
    DriverOperation operation;
} Driver;

typedef void (*DriverServiceBusOperationUnRegisterDriver)(struct DriverServiceBus *bus, Driver driver);

typedef void (*DriverServiceBusOperationRegisterDriver)(struct DriverServiceBus *bus, Driver driver);

typedef void (*DriverServiceBusOperationSubscribeDriver)(struct DriverServiceBus *bus, Driver driver);

typedef struct DriverBusOperation {
    DriverServiceBusOperationRegisterDriver registerDriver;
    DriverServiceBusOperationUnRegisterDriver unRegisterDriver;
    DriverServiceBusOperationSubscribeDriver subscribeDriver;
} DriverBusOperation;

typedef struct DriverServiceBus {
    DriverBusOperation operation;
} DriverServiceBus;

DriverServiceBus *driver_service_bus_create(struct DriverServiceBus *driverServiceBus);

#endif //SYNESTIAOS_BUS_H
