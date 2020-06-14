#include <interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <synestia_os_hal.h>
#include <kheap.h>

void clean_bss(uint8_t *start, const uint8_t *end) {
    uint32_t i;
    for (i = 0; start + i < end; i++) {
        *(start + i) = '\0';
    }
}

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

void test_heap_alloc_func(void *ptr, uint32_t size){
    printf("[Heap] alloc %d bytes\n",size);
}

void test_heap_free_func(void *ptr){
    printf("[Heap] free \n");
}


void kernel_main(void) {
    print_splash();

    init_interrupt();

    init_bsp();



    /**
     * swi test
     */
    swi(1);
    swi(2);

    /**
     * printf test
     */
    printf("test:%d\n", 12);

    /**
     * heap test
     */
    heap_init();
    heap_set_alloc_callback(test_heap_alloc_func);
    heap_set_free_callback(test_heap_free_func);
    int *testInt = (int *) heap_alloc(sizeof(int) * 2);
    testInt[0] = 1;
    testInt[1] = 2;

    printf("test 1:%d\n", testInt[0]);
    printf("test 2:%d\n", testInt[1]);

    heap_free(testInt);
}
