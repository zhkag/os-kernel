//
// Created by zhkag on 24-10-1.
//

#include "irq.h"
#include <os.h>

volatile os_atomic_t os_irq_count = 0;

// void os_irq_enter(void)
// {
//     os_atomic_inc(&os_irq_count);
// }
// void os_irq_leave(void)
// {
//     os_atomic_dec_return(&os_irq_count);
// }

os_atomic_t os_irq_enter_cleanup(void)
{
    return os_atomic_inc_return(&os_irq_count);
}
void os_irq_leave_cleanup(OS_UNUSED volatile os_atomic_t *unused)
{
    os_atomic_dec_return(&os_irq_count);
}

os_atomic_t os_irq_get_count(void)
{
    return os_atomic_load(&os_irq_count);
}



