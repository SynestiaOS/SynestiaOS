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

void draw_chess_board() {

    gfx_fill(0, 0, 1024, 768, 0x00A86E3A);

    // top
    gfx_fill(0, 0, 1024, 30, 0x00FFFF00);

    // bottom
    gfx_fill(0, 738, 1024, 768, 0x00FFFF00);

    // left
    gfx_fill(0, 0, 30, 768, 0x00FFFF00);

    // right
    gfx_fill(994, 0, 1024, 768, 0x00FFFF00);

    for (int i = 64; i < 1024; i += 64) {
        gfx_draw_line(i, 0, i, 768, 0x00FFFFFF);
    }

    for (int i = 64; i < 748; i += 64) {
        gfx_draw_line(0, i, 1024, i, 0x00FFFFFF);
    }


    for (int i = 64; i < 1024 - 64; i += 64) {
        for (int j = 64; j < 768 - 64; j += 64) {
            if ((i * j) % 3 == 0) {
                gfx_fill_circle(i, j, 26, 0x00FF0000);
            } else {
                gfx_fill_circle(i, j, 26, 0x000000FF);
            }
        }
    }

    gfx_fill_triangle(0, 0, 0, 150, 150, 0, 0x00FF00FF);

    gfx_fill_triangle(1024 - 150, 0, 1024, 0, 1024, 150, 0x00FF00FF);
}

void kernel_main(void) {

    print_splash();

    vmm_init();

    kheap_init(); // this is just for test
    __run_tests();

    kheap_init();

    gpu_init();

    draw_chess_board();

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
