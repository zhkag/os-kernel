//
// Created by zhkag on 24-10-1.
//

#ifndef OS_SCHEDULER_H
#define OS_SCHEDULER_H
#include <thread.h>

void os_scheduler_init(void);
void scheduler_thread_remove(struct os_thread * thread);
void scheduler_thread_add(struct os_thread * thread);
void os_scheduler_start(void);
void os_schedule(void);
struct os_thread * os_thread_self(void);
void os_switch_thread(struct os_thread * form,struct os_thread * to);
void os_thread_tick_decrease(void);

void os_context_switch_to(void* to);
void os_context_switch(void* from, void* to);
void os_context_switch_interrupt(void* from, void* to,struct os_thread * from_thread,struct os_thread * to_thread);

#endif //OS_SCHEDULER_H
