//
// Created by zhkag on 24-10-1.
//

#include "string.h"
#include "timer.h"
#include "tick.h"

OS_LIST_INIT(os_timer_list);
OS_LIST_INIT(os_timer_run_list);


uint32_t os_timer_init(struct os_timer *timer,
                       const char *name,
                       int (*entry)(void *parameter),
                       void *parameter,
                       const uint32_t period,
                       const uint8_t type)
{
    strncpy(timer->name, name, 8);
    timer->entry = entry;
    timer->parameter = parameter;
    timer->period = period;
    timer->type = type;
    timer->state = timer_init;
    os_list_insert_before(&os_timer_list,&timer->all_list);
    return 0;
}

uint32_t os_timer_set_period(struct os_timer *timer,const uint32_t period)
{
    timer->period = period;
    return 0;
}

uint32_t os_timer_start(struct os_timer *timer)
{
    timer->timeout_tick = os_tick_get() + timer->period;

    struct os_list *head = &os_timer_run_list;
    for (struct os_list *pos = head->next; pos != head; pos = pos->next)
    {
        struct os_timer * timer_node = CONTAINER_OF(pos, struct os_timer, list);
        if (timer_node->timeout_tick > timer->timeout_tick)
        {
            os_list_insert_before(&timer_node->list, &timer->list);
            break;
        }
    }
    if (timer->list.next == timer->list.prev)
    {
        os_list_insert_before(head, &timer->list);
    }

    return 0;
}

void os_timer_check(void)
{
    const uint32_t tick = os_tick_get();
    const struct os_list *head = &os_timer_run_list;
    for (struct os_list *pos = head->next; pos != head; pos = pos->next)
    {
        struct os_timer * timer = CONTAINER_OF(pos, struct os_timer, list);

        if (timer->timeout_tick <= tick)
        {
            timer->entry(timer->parameter);
            if (timer->type == timer_cycle)
            {
                os_list_del(pos);
                os_timer_start(timer);
            }
        }
    }
}
