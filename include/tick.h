//
// Created by zhkag on 24-10-1.
//

#ifndef TICK_H
#define TICK_H

#include "stdint.h"

typedef uint32_t os_tick_t;
void os_tick_inc(void);
os_tick_t os_tick_get(void);

#endif //TICK_H
