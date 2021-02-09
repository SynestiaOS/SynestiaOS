
#include "kernel/log.h"
#include "libc/stdbool.h"

#define MAX_FUNC_LEN 0x1000

/* non-leaf function prologue:
 * push	{r?, r11, lr}
 * add	r11, sp, #?
 */
static const unsigned int nonleaf_prologue[2] = { 0xe92d4800, 0xe28db000 };

/* leaf function prologue:
 * str	r11, [sp, #-?]!
 */
static const unsigned int leaf_prologue[] = { 0xe52db000 };

static void find_func_header(unsigned int *instr)
{
    unsigned int i;

    for (i = 0; (i < MAX_FUNC_LEN) && (0 != instr); i++, instr--) {
        if (((0xffffff00 & *instr) == leaf_prologue[0])
         || (((0xffff4800 & *instr) == nonleaf_prologue[0]) // if only {r11, lr} are pushed
          && ((0xffffff00 & *(instr + 1)) == nonleaf_prologue[1]))) {
            LogError("func: 0x%x\n", instr);
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

bool func_is_leaf(unsigned int *instr)
{
    unsigned int i;

    for (i = 0; (i < MAX_FUNC_LEN) && (0 != instr); i++, instr--) {
        if ((0xffffff00 & *instr) == leaf_prologue[0]) {
            return true;
        }
    }
    return false;
}