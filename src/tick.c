//
// Created by zhkag on 24-10-1.
//

#include "tick.h"
#include "os.h"
#include "timer.h"

static volatile os_atomic_t os_tick = 0;

void os_tick_inc(){
    os_atomic_add(&os_tick, 1);
    os_thread_tick_decrease();
    os_timer_check();
}

os_tick_t os_tick_get(void)
{
    return os_atomic_load(&os_tick);
}

void os_tick_set(const os_tick_t tick)
{
    os_atomic_store(&os_tick, tick);
}

