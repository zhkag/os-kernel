//
// Created by zhkag on 24-10-1.
//

#include "idle.h"
#include "thread.h"

static uint8_t idle_thread_stack[512];
struct os_thread idle_thread;

static void idle_thread_entry(void *parameter)
{
    while (1)
    {
        os_schedule();
    }
}

void os_idle_init(void)
{
    os_thread_init(&idle_thread, "idle", idle_thread_entry, NULL,
                            idle_thread_stack, sizeof(idle_thread_stack), 31, 20);
    os_thread_startup(&idle_thread);
}
