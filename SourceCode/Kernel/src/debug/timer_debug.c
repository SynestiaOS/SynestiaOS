#include <kernel/ktimer.h>
#include <kernel/log.h>

extern KernelTimerManager kernelTimerManager;

void dump_timer_statistics(const char *info)
{
    if (info != nullptr) {
        LogInfo("---%s---\n", info)
    }
    LogInfo("sysRuntimeMs = %d ms\n", kernelTimerManager.sysRuntimeMs)
    if (kernelTimerManager.timerNodes == nullptr) {
        LogInfo("There is no timer in nodes!\n")
        return;
    }

    LogInfo("timer node count = %d\n", klist_size(&kernelTimerManager.timerNodes->list));

    struct ListNode *node = &kernelTimerManager.timerNodes->list;
    uint32_t count = 0;
    while (node != nullptr) {
        struct KernelTimer *timer = getNode(node, struct KernelTimer, list);
        LogInfo("timer%d, remainTime: %d, deadline: %d\n", count, timer->remainTime, timer->deadline);
        node = node->next;
        count++;
    }
    LogInfo("Tick.name = %s\n", kernelTimerManager.timerManagerTick.name)
    LogInfo("tick.next = 0x%x, prev = 0x%x\n", kernelTimerManager.timerManagerTick.node.next, kernelTimerManager.timerManagerTick.node.prev);
    ListNode tick_node = kernelTimerManager.timerManagerTick.node;
    while (tick_node.next != nullptr) {
        LogInfo("tick_node.next = 0x%x, prev = 0x%x\n", tick_node.next, tick_node.prev);
        tick_node = *tick_node.next;
    }

}
void timer_test()
{
    void *timer1 = kernelTimerManager.operation.createTimer(&kernelTimerManager, 100);
    dump_timer_statistics("create timer 1");
    void *timer2 = kernelTimerManager.operation.createTimer(&kernelTimerManager, 300);
    dump_timer_statistics("create timer 2");
    void *timer3 = kernelTimerManager.operation.createTimer(&kernelTimerManager, 400);
    dump_timer_statistics("create timer 3");
    kernelTimerManager.operation.releaseTimer(&kernelTimerManager, timer1);
    dump_timer_statistics("free timer 1");

    kernelTimerManager.operation.releaseTimer(&kernelTimerManager, timer2);
    dump_timer_statistics("free timer 2");

    kernelTimerManager.operation.releaseTimer(&kernelTimerManager, timer3);
    dump_timer_statistics("free timer 3");
}

