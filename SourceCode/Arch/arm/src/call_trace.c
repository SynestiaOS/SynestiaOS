
#include "kernel/log.h"

static void find_func_header(unsigned int *instr)
{
    static const unsigned int prologue[2] = { 0xe92d4800, 0xe28db000 };
    unsigned int i;

#define MAX_FUNC_LEN 0x1000
    for (i = 0; (i < MAX_FUNC_LEN) && (0 != instr); i++, instr--) {
        if (((0xffff4800 & *(instr - 1)) == prologue[0]) // if only {r11, lr} are pushed
         && ((0xffffff00 & *instr) == prologue[1])) {
            LogError("func: 0x%x\n", instr - 1);
            return;
        }
    }
    LogError("func: can not find function!!!\n");
}

void dump_calltrace(void)
{
    unsigned int *lr, *fp;
    unsigned int *func;

    __asm__ __volatile__("str lr, %0\n\t" : "=m"(lr));
    __asm__ __volatile__("str r11, %0\n\t" : "=m"(fp));

    LogError("callstack info:\n");
    while (1) {
        lr = (unsigned int *) fp[0];
        fp = (unsigned int *) fp[-1];
        if (0 == fp) {
            break;
        }
        // printf("fp: 0x%x, lr 0x%x\n", fp, lr);
        find_func_header(lr);
    }
    LogError("callstack end\n");
}
