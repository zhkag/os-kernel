//
// Created by zhkag on 24-10-1.
//

#include "scheduler.h"
#include "list.h"
#include <os.h>
#include <atomic.h>

static struct os_list os_thread_priority[32];
static uint32_t os_thread_priority_mask = 0;
static struct os_thread * current_thread = NULL;

void scheduler_thread_remove(struct os_thread *thread)
{
    os_list_del(&thread->list);
    if (os_list_is_empty(&os_thread_priority[thread->current_priority]))
    {
        os_thread_priority_mask &= ~(1 << thread->current_priority);
    }
}

struct os_thread * os_thread_self(void)
{
    return current_thread;
}

void os_set_current_thread(struct os_thread * thread)
{
    if (thread->stat == thread_ready)
    {
        thread->stat = thread_running;
        scheduler_thread_remove(thread);
        current_thread = thread;
    }
}

static __inline struct os_thread * get_highest_priority_thread()
{
    const int priority = __os_ffs(os_thread_priority_mask) - 1;
    return CONTAINER_OF(os_thread_priority[priority].next, struct os_thread, list);
}

void os_scheduler_init(void)
{
    for (uint32_t i = 0; i < 32; i++)
    {
        os_list_init(&os_thread_priority[i]);
    }
}

void scheduler_thread_add(struct os_thread *thread)
{
    thread->stat = thread_ready;
    os_list_insert_after(&os_thread_priority[thread->current_priority], &thread->list);
    os_thread_priority_mask |= 1 << thread->current_priority;
}


void os_scheduler_start(void)
{
    struct os_thread * thread = get_highest_priority_thread();
    os_set_current_thread(thread);
    rt_hw_context_switch_to(&thread->sp);
}

void os_schedule()
{
    OS_IRQ_DISABLE
    struct os_thread * highest_thread = get_highest_priority_thread();
    struct os_thread * form_thread = os_thread_self();
    if (form_thread->current_priority < highest_thread->current_priority)
        return;
    // if (os_list_is_empty(&form_thread->list))
        scheduler_thread_add(form_thread);
    os_switch_thread(form_thread,highest_thread);
}

void os_switch_thread(struct os_thread * form,struct os_thread * to)
{
    os_set_current_thread(to);
    if (os_irq_get_count() == 0)
    {
        rt_hw_context_switch(&form->sp,&to->sp);
    }
    else
    {
        rt_hw_context_switch_interrupt(&form->sp, &to->sp, form, to);
    }
}


void os_thread_tick_decrease(void)
{
    struct os_thread * thread = os_thread_self();
    if(os_atomic_dec_return(&thread->remaining_tick) == 0)
    {
        os_atomic_store(&thread->remaining_tick,thread->init_tick);
        os_schedule();
    }
}