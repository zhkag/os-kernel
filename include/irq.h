//
// Created by zhkag on 24-10-1.
//

#ifndef IRQ_H
#define IRQ_H
#include <atomic.h>

uint32_t os_irq_disable_cleanup();
void os_irq_enable_cleanup(uint32_t *level);
os_atomic_t os_irq_enter_cleanup(void);
void os_irq_leave_cleanup(volatile os_atomic_t *unused);
os_atomic_t os_irq_get_count(void);

#define OS_IRQ_ENTER OS_CLEANUP(os_irq_leave_cleanup) os_atomic_t count = os_irq_enter_cleanup();

#define OS_IRQ_DISABLE OS_CLEANUP(os_irq_enable_cleanup) uint32_t level = os_irq_disable_cleanup();

#endif //IRQ_H
