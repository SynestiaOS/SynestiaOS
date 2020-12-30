//
// Created by XingfengYang on 2020/12/30.
//

#include "arm/cpu.h"


RegisterCPSR svcModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10011;
    return cpsr;
}

RegisterCPSR userModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10000;
    return cpsr;
}

RegisterCPSR fiqModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10001;
    return cpsr;
}

RegisterCPSR irqModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10010;
    return cpsr;
}

RegisterCPSR sysModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b11111;
    return cpsr;
}
