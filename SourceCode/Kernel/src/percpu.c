//
// Created by XingfengYang on 2020/6/30.
//

#include "kernel/percpu.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "kernel/thread.h"

extern Heap kernelHeap;
PerCpu *perCpu = nullptr;

KernelStatus percpu_default_insert_thread(PerCpu *perCpu, Thread *thread) {
    LogWarn("[PerCpu]: insert thread '%s' to cpu '%d'.\n", thread->name, perCpu->cpuId);
    perCpu->rbTree.operations.insert(&perCpu->rbTree, &thread->rbNode);
    perCpu->priority += thread->priority;
    thread->currCpu = perCpu->cpuId;
    return OK;
}

Thread *percpu_default_remove_thread(PerCpu *perCpu, Thread *thread) {
    LogWarn("[PerCpu]: remove thread '%s' from cpu '%d'.\n", thread->name, perCpu->cpuId);
    RBNode *node = perCpu->rbTree.operations.remove(&perCpu->rbTree, &thread->rbNode);
    perCpu->priority -= thread->priority;
    thread->lastCpu = perCpu->cpuId;
    return getNode(node, Thread, rbNode);
}

Thread *percpu_default_get_next_thread(PerCpu *perCpu) {
    RBNode *node = perCpu->rbTree.operations.getMin(&perCpu->rbTree);
    if (node == nullptr) {
        // TODO: migration from other core.
        LogWarn("[PerCpu]: get min thread null.\n");
        return perCpu->idleThread;
    }
    Thread *thread = getNode(node, Thread, rbNode);
    if (thread == nullptr) {
        return perCpu->idleThread;
    }
    return thread;
}

KernelStatus percpu_default_init(PerCpu *perCpu, CpuNum num, Thread *idleThread) {
    perCpu->idleThread = idleThread;
    perCpu->cpuId = num;
    perCpu->priority = 0;
    perCpu->status.idleTime = 0;
    perCpu->currentThread = nullptr;
    perCpu->rbTree.root = nullptr;
    rb_tree_init(&perCpu->rbTree);
    perCpu->waitThreadQueue.next = nullptr;
    perCpu->waitThreadQueue.prev = nullptr;
    LogInfo("[PerCpu]: precpu '%d' inited.\n", num);
    return OK;
}

KernelStatus percpu_create(CpuNum cpuNum) {
    perCpu = (PerCpu *) kernelHeap.operations.calloc(&kernelHeap, cpuNum, sizeof(PerCpu));
    if (perCpu == nullptr) {
        return ERROR;
    }
    for (CpuNum cpuId = 0; cpuId < cpuNum; cpuId++) {
        perCpu[cpuId].operations.init = (PerCpuInit) percpu_default_init;
        perCpu[cpuId].operations.insertThread = (PerCpuInsertThread) percpu_default_insert_thread;
        perCpu[cpuId].operations.removeThread = (PerCpuRemoveThread) percpu_default_remove_thread;
        perCpu[cpuId].operations.getNextThread = (PerCpuGetNextThread) percpu_default_get_next_thread;
    }
    return OK;
}

PerCpu *percpu_get(CpuNum cpuNum) { return &perCpu[cpuNum]; }

PerCpu *percpu_min_priority(CpuNum cpuMask) {
    CpuNum minMaskCPU = 0;
    for (CpuNum i = 0; i < SMP_MAX_CPUS; i++) {
        if (cpu_number_to_mask(i) & cpuMask) {
            minMaskCPU = i;
            break;
        }
    }
    PerCpu *min = &perCpu[minMaskCPU];
    for (CpuNum cpuId = minMaskCPU; cpuId < SMP_MAX_CPUS; cpuId++) {
        if (perCpu[cpuId].priority < min->priority && (0x1 << cpuId & cpuMask)) {
            min = &perCpu[cpuId];
        }
    }
    return min;
}
