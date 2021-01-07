//
// Created by XingfengYang on 2021/1/7.
//

#include "kernel/bus.h"


void driver_service_bus_default_unregister_driver(struct DriverServiceBus *bus, Driver driver) {

}

void driver_service_bus_default_register_driver(struct DriverServiceBus *bus, Driver driver) {

}

void driver_service_bus_default_subscribe_driver(struct DriverServiceBus *bus, Driver driver) {

}


DriverServiceBus *driver_service_bus_create(struct DriverServiceBus *driverServiceBus) {
    driverServiceBus->operation.registerDriver = driver_service_bus_default_register_driver;
    driverServiceBus->operation.unRegisterDriver = driver_service_bus_default_unregister_driver;
    driverServiceBus->operation.subscribeDriver = driver_service_bus_default_subscribe_driver;
}
