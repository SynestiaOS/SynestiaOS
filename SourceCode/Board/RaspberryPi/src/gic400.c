//
// Created by XingfengYang on 2021/1/28.
//
#include "kernel/log.h"
#include "raspi2/gic400.h"

void gic400_init(void *interruptControllerBase) {
    LogInfo("[GIC400] init.\n")
    GIC400 gic400;

    gic400.gic400Distributor = (GIC400Distributor *) (interruptControllerBase + 0x1000);
    gic400.gic400CpuInterface = (GIC400CpuInterface *) (interruptControllerBase + 0x2000);

    /* Disable the controller so we can configure it before it passes any
       interrupts to the CPU */
    gic400.gic400Distributor->ctl = GIC400_CTL_DISABLE;

    /* Get the number of interrupt lines implemented in the GIC400 controller */
    int numberOfInterrupts = GIC400_TYPE_ITLINESNUMBER_GET(gic400.gic400Distributor->type) * 32;

    /* The actual number returned by the ITLINESNUMBER is the number of registered implemented.
       The actual number of interrupt lines available is (ITLINESNUMBER * 32) */
    for (int i = 0; i < numberOfInterrupts; i++) {
        /* Deal with register sets that have 32-interrupts per register */
        if ((i % 32) == 0) {
            /* Disable this block of 32 interrupts, clear the pending and active flags */
            gic400.gic400Distributor->icenable[i / 32] = 0xFFFFFFFF;
            gic400.gic400Distributor->icpend[i / 32] = 0xFFFFFFFF;
            gic400.gic400Distributor->icactive[i / 32] = 0xFFFFFFFF;
        }
        /* Deal with interrupt configuration. The configuration registers are 32-bit wide and
        have 2-bit configuration for each interrupt */
        gic400.gic400Distributor->icfg[i / 16] &= (0x3 << (i % 16));
        gic400.gic400Distributor->icfg[i / 16] |= (GIC400_ICFG_LEVEL_SENSITIVE << (i % 16));

        /* Deal with register sets that have one interrupt per register */
        gic400.gic400Distributor->ipriority[i] = 0xA0;
        gic400.gic400Distributor->istargets[i] = GIC400_TARGET_CPU0;
    }

    gic400.gic400Distributor->ctl = GIC400_CTL_ENABLE;

    gic400.gic400CpuInterface->pm = 0xF0;
    gic400.gic400CpuInterface->ctl = GIC400_CTL_ENABLE;

    LogInfo("[GIC400] inited.\n")
}
