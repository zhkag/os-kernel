#include "thread.h"

#include <timer.h>

#include "scheduler.h"

#include "list.h"

OS_LIST_INIT(os_thread_list);

static void thread_exit(int status)
{
    // struct os_thread *thread;
    // rt_base_t critical_level;
    //
    // /* get current thread */
    // thread = rt_thread_self();
    //
    // critical_level = rt_enter_critical();
    //
    // rt_thread_close(thread);
    //
    // /* insert to defunct thread list */
    // rt_thread_defunct_enqueue(thread);
    //
    // rt_exit_critical_safe(critical_level);

    /* switch to next task */
    // os_schedule();
}

static int thread_timeout(void *parameter)
{
    return 0;
}

uint32_t os_thread_set_priority(struct os_thread *thread, const uint8_t priority)
{
    thread->current_priority = priority;
    if (thread->stat == thread_ready)
    {
        scheduler_thread_remove(thread);
        scheduler_thread_add(thread);
    }
    return 0;
}

uint32_t os_thread_init(struct os_thread *thread,
                        const char       *name,
                        int (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        const uint32_t   stack_size,
                        const uint8_t    priority,
                        const uint32_t   tick)
{
    strncpy(thread->name, name, 8);
    thread->entry = entry;
    thread->parameter = parameter;
    thread->stack_addr = stack_start;
    thread->stack_size = stack_size;
    thread->current_priority = priority;
    os_atomic_store(&thread->init_tick,tick);
    os_atomic_store(&thread->remaining_tick,tick);
    thread->sp = (void *)os_stack_init(thread->entry, thread->parameter,
                                      (uint8_t *)((char *)thread->stack_addr + thread->stack_size - sizeof(uint32_t)),
                                      (void *)thread_exit);
    thread->stat = thread_initialization;
    os_list_insert_before(&os_thread_list,&thread->all_list);
    os_timer_init(&thread->timer,name,thread_timeout,NULL,0,timer_one_shot);
    return 0;
}

uint32_t os_thread_startup(struct os_thread *thread){
    scheduler_thread_add(thread);
    return 0;
}

uint32_t os_thread_tick(const uint32_t tick){
    struct os_thread * thread = os_thread_self();
    thread->timer.period = tick;
    os_timer_start(&thread->timer);
    return 0;
}
