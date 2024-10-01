//
// Created by zhkag on 24-10-1.
//

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "list.h"
#include <generic.h>

enum os_timer_state
{
    timer_init,
    timer_start,
    timer_stop,
};

enum os_timer_type
{
    timer_one_shot,
    timer_cycle,
};

struct os_timer
{
    char        name[8];
    uint8_t     state;
    uint8_t     type;
    int (*entry)(void *parameter);
    void *parameter;
    uint32_t period;
    uint32_t timeout_tick;
    struct os_list list;
    struct os_list all_list;
};

GENERIC_NAME(os_timer)

uint32_t os_timer_init(struct os_timer *timer,
                       const char *name,
                       int (*entry)(void *parameter),
                       void *parameter,
                       const uint32_t period,
                       const uint8_t type);
uint32_t os_timer_start(struct os_timer *timer);

void os_timer_check(void);

#endif //TIMER_H
