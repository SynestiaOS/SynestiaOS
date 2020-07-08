#include <interrupt.h>
#include <stdlib.h>
#include <synestia_os_hal.h>
#include <kheap.h>
#include <vmm.h>
#include <sched.h>
#include <gpu.h>
#include <gui_button.h>
#include <gui_window.h>
#include <gui_label.h>
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

void draw_gui() {
    gfx2d_draw_logo(0, 0, 0xFFFFFF);

    GUIButton synestiaOSButton;
    gui_button_create(&synestiaOSButton);
    synestiaOSButton.component.size.height = 32;
    synestiaOSButton.component.padding.top = 12;
    gui_button_init(&synestiaOSButton, 32, 0, "SynestiaOS");
    gui_button_draw(&synestiaOSButton);

    GUILabel bar;
    gui_label_create(&bar);
    bar.component.size.width = 1024 - 32 - synestiaOSButton.component.size.width;
    bar.component.size.height = 32;
    bar.component.background.r = 0x00;
    bar.component.background.g = 0x78;
    bar.component.background.b = 0xD4;
    gui_label_init(&bar, 32 + synestiaOSButton.component.size.width, 0, "");
    gui_label_draw(&bar);

    GUILabel synestiaOSLabel;
    gui_label_create(&synestiaOSLabel);
    synestiaOSLabel.component.size.width = 100;
    gui_label_init(&synestiaOSLabel, 10, 40, "Welcome to Synestia Operation System.");
    gui_label_draw(&synestiaOSLabel);

    GUILabel synestiaOSLabel2;
    gui_label_create(&synestiaOSLabel2);
    gui_label_init(&synestiaOSLabel2, 200, 40, "Welcome to Synestia Operation System.");
    gui_label_draw(&synestiaOSLabel2);

    GUIWindow window;
    gui_window_create(&window);
    gui_window_init(&window, 100, 100, "SynestiaOS");
    gui_window_draw(&window);

    GUIWindow window1;
    gui_window_create(&window1);
    gui_window_init(&window1, 150, 150, "SynestiaOS 1");
    gui_window_draw(&window1);

    GUIButton ok;
    gui_button_create(&ok);
    synestiaOSButton.component.size.height = 32;
    synestiaOSButton.component.padding.top = 12;
    gui_button_init(&ok, 10, 0, "Inner Window Button");

    GUILabel label;
    gui_label_create(&label);
    label.component.size.height = 32;
    label.component.padding.top = 12;
    gui_label_init(&label, 10, 50, "Inner Window Label");

    GUIWindow window2;
    gui_window_create(&window2);
    gui_window_add_children(&window2, &(ok.component));
    gui_window_add_children(&window2, &(label.component));
    gui_window_init(&window2, 200, 200, "SynestiaOS 2");
    gui_window_draw(&window2);
}

void kernel_main(void) {

    print_splash();

    vmm_init();

    kheap_init();

    gpu_init();

    draw_gui();

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
