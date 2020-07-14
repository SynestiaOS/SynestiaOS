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
#include <gui_panel.h>
#include <gui_container.h>
#include <font8bits.h>

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

uint32_t hour, minutes, second = 0;

void draw_task_bar() {
    uint32_t *barBuffer = (uint32_t *) kheap_alloc(1024 * 32 * 4);

    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 31; j++) {
            barBuffer[j * 1024 + i] = ((FLUENT_PRIMARY_COLOR >> 16) & 0xFF - j) << 16 | ((FLUENT_PRIMARY_COLOR >> 8) & 0xFF - j) << 8 | (FLUENT_PRIMARY_COLOR & 0xFF - j);
        }
    }
    for (int i = 0; i < 1024; i++) {
        barBuffer[31 * 1024 + i] = 0x999999;
    }
    gfx2d_draw_bitmap(0, 0, 1024, 32, barBuffer);
    gfx2d_draw_logo(0, 0, 0xFFFFFF);
}

GUILabel hourLabel;
GUILabel colon;
GUILabel minuteLabel;
GUILabel colon2;
GUILabel secondLabel;

void draw_time() {
    gui_label_create(&hourLabel);
    hourLabel.component.foreground.r = 0xFF;
    hourLabel.component.foreground.g = 0xFF;
    hourLabel.component.foreground.b = 0xFF;
    hourLabel.component.size.height = 32;
    hourLabel.component.padding.top = 12;
    hourLabel.component.colorMode = TRANSPARENT;
    char hour_str[10] = {'\0'};
    char *hour_str_ = itoa(hour, &hour_str, 10);
    gui_label_init(&hourLabel, 1000 - 60, 0, hour_str_);
    gui_label_draw(&hourLabel);

    gui_label_create(&colon);
    colon.component.foreground.r = 0xFF;
    colon.component.foreground.g = 0xFF;
    colon.component.foreground.b = 0xFF;
    colon.component.size.height = 32;
    colon.component.padding.top = 12;
    colon.component.colorMode = TRANSPARENT;
    gui_label_init(&colon, 1000 - 45, 0, ":");
    gui_label_draw(&colon);

    gui_label_create(&minuteLabel);
    minuteLabel.component.foreground.r = 0xFF;
    minuteLabel.component.foreground.g = 0xFF;
    minuteLabel.component.foreground.b = 0xFF;
    minuteLabel.component.size.height = 32;
    minuteLabel.component.padding.top = 12;
    minuteLabel.component.colorMode = TRANSPARENT;
    char minute_str[10] = {'\0'};
    char *minute_str_ = itoa(minutes, &minute_str, 10);
    gui_label_init(&minuteLabel, 1000 - 35, 0, minute_str_);
    gui_label_draw(&minuteLabel);

    gui_label_create(&colon2);
    colon2.component.foreground.r = 0xFF;
    colon2.component.foreground.g = 0xFF;
    colon2.component.foreground.b = 0xFF;
    colon2.component.size.height = 32;
    colon2.component.padding.top = 12;
    colon2.component.colorMode = TRANSPARENT;
    gui_label_init(&colon2, 1000 - 20, 0, ":");
    gui_label_draw(&colon2);

    gui_label_create(&secondLabel);
    secondLabel.component.foreground.r = 0xFF;
    secondLabel.component.foreground.g = 0xFF;
    secondLabel.component.foreground.b = 0xFF;
    secondLabel.component.size.height = 32;
    secondLabel.component.padding.top = 12;
    secondLabel.component.colorMode = TRANSPARENT;
    char second_str[10] = {'\0'};
    char *second_str_ = itoa(second, &second_str, 10);
    gui_label_init(&secondLabel, 1000 - 10, 0, second_str_);
    gui_label_draw(&secondLabel);
}

GUIWindow window;
GUIWindow window1;
GUILabel labelIdle1;
GUILabel labelIdle2;

uint32_t idle_0_count = 0;
uint32_t idle_1_count = 0;

void demo_desktop() {
    draw_time();

    gui_window_create(&window);
    window.component.size.width = 510;
    window.component.size.height = 500;
    gui_window_init(&window, 0, 32, "Process 1");

    gui_label_create(&labelIdle1);
    labelIdle1.component.foreground.r = 0x00;
    labelIdle1.component.foreground.g = 0x00;
    labelIdle1.component.foreground.b = 0x00;
    labelIdle1.component.colorMode = TRANSPARENT;
    char idle_1_str[10] = {'\0'};
    gui_label_init(&labelIdle1, 0, 0, itoa(idle_0_count, &idle_1_str, 10));
    gui_window_add_children(&window, &(labelIdle1.component));
    gui_window_draw(&window);

    gui_window_create(&window1);
    window1.component.size.width = 510;
    window1.component.size.height = 500;
    gui_window_init(&window1, 512, 32, "Process 2");
    gui_label_create(&labelIdle2);
    labelIdle2.component.foreground.r = 0x00;
    labelIdle2.component.foreground.g = 0x00;
    labelIdle2.component.foreground.b = 0x00;
    labelIdle2.component.colorMode = TRANSPARENT;
    char idle_2_str[10] = {'\0'};
    gui_label_init(&labelIdle2, 0, 0, itoa(idle_1_count, &idle_2_str, 10));
    gui_window_add_children(&window1, &(labelIdle2.component));
    gui_window_draw(&window1);
}

Thread *t0;
Thread *t1;

void xx() {
    if (second == 60) {
        second = 0;
        minutes++;
        if (minutes == 60) {
            minutes = 0;
            hour++;
            if (hour == 24) {
                hour = 0;
            }
        }
    }
    second++;

    //Switch To thread
    if ((second % 2) == 0) {
        schd_switch_to(t0);
    } else {
        schd_switch_to(t1);
    }
}

uint32_t *idle0(int arg) {
    uint32_t i = 0;
    uint32_t j = 0;
    while (1) {
        i = 0;
        printf("IDLE 0, count = %d \n", idle_0_count);
        idle_0_count++;

        disable_interrupt();
        char idle_1_str[10] = {'\0'};
        gui_label_init(&labelIdle1, 0, 0, itoa(idle_0_count, &idle_1_str, 10));
        gui_window_draw(&window);
        enable_interrupt();
    }
    //asm volatile("wfi");x
}

uint32_t *idle1(int arg) {
    uint32_t i = 0;
    uint32_t j = 0;
    while (1) {
        i = 0;
        printf("IDLE 1, count = %d \n", idle_1_count);
        idle_1_count++;

        disable_interrupt();
        char idle_2_str[10] = {'\0'};
        gui_label_init(&labelIdle2, 0, 0, itoa(idle_1_count, &idle_2_str, 10));
        gui_window_draw(&window1);
        enable_interrupt();
    }
    //asm volatile("wfi");
}

TimerHandler t;

void kernel_main(void) {

    print_splash();

    vmm_init();

    kheap_init();

    init_bsp();

    init_interrupt();

    //  schd_init();

    t0 = thread_create("IDLE0", idle0, 0, 0);
    t1 = thread_create("IDLE1", idle1, 1, 0);

    gpu_init();

    t.node.next = nullptr;
    t.node.prev = nullptr;
    t.timer_interrupt_handler = &xx;

    register_time_interrupt(&t);

    gfx2d_draw_bitmap(0, 0, 1024, 768, desktop());
    draw_task_bar();
    demo_desktop();
}
