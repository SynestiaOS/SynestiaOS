#include <interrupt.h>
#include <stdlib.h>
#include <synestia_os_hal.h>
#include <kheap.h>
#include <vmm.h>
#include <tests.h>
#include <sched.h>
#include <gpu.h>
#include <gfx2d.h>

void print_splash() {
    const char *str = "   _____                       _   _       \n"
                      "  / ____|                     | | (_)      \n"
                      " | (___  _   _ _ __   ___  ___| |_ _  __ _ \n"
                      "  \\___ \\| | | | '_ \\ / _ \\/ __| __| |/ _` |\n"
                      "  ____) | |_| | | | |  __/\\__ \\ |_| | (_| |\n"
                      " |_____/ \\__, |_| |_|\\___||___/\\__|_|\\__,_|\n"
                      "          __/ |                            \n"
                      "         |___/                          \n";

    print(str);
}

void kernel_main(void) {

    print_splash();

    vmm_init();

    kheap_init(); // this is just for test
    __run_tests();

    kheap_init();

    gpu_init();

    gfx_draw_line(0, 0, 100, 100, 0x00FF0000);

    gfx_draw_circle(100, 100, 30, 0x0000FF00);

    gfx_draw_triangle(200, 200, 280, 200, 200, 280, 0x000000FF);

    gfx_fill_triangle(500, 400, 600, 500, 500, 400, 0x00FFFF00);

    gfx_fill(300, 0, 400, 100, 0x00FF00FF);

    gfx_fill_circle(500, 200, 60, 0x0000FFFF);

    init_interrupt();

    init_bsp();

    schd_init();

    schd_switch_to(thread_create_idle_thread(0));

    /**
     * swi test
     */
    swi(1);
    swi(2);

    /**
     * printf test
     */
    printf("test:%d \n", 12);
    printf("test:%s \n", "lalala");

    /**
     * heap test
     */
    KernelStatus kernelHeapInitStatus = kheap_init();
    if (kernelHeapInitStatus != OK) {
        printf("[heap] kernel heap init failed.\n");
    }
    int *testInt = (int *) kheap_alloc(sizeof(int) * 2);
    testInt[0] = 1;
    testInt[1] = 2;

    printf("test 1:%d \n", testInt[0]);
    printf("test 2:%d \n", testInt[1]);

    KernelStatus kernelHeapFreeStatus = kheap_free(testInt);
    if (kernelHeapFreeStatus != OK) {
        printf("[heap] kernel heap free failed.\n");
    }
}
