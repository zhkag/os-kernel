//
// Created by zhkag on 24-10-1.
//

#ifndef ATOMIC_H
#define ATOMIC_H
#include <stdint.h>

typedef volatile uint32_t os_atomic_t;

os_atomic_t os_atomic_add(os_atomic_t *addr, uint32_t value);
os_atomic_t os_atomic_sub(os_atomic_t *addr, uint32_t value);
os_atomic_t os_atomic_inc(os_atomic_t *addr);
os_atomic_t os_atomic_dec(os_atomic_t *addr);
os_atomic_t os_atomic_inc_return(os_atomic_t *addr);
os_atomic_t os_atomic_dec_return(os_atomic_t *addr);
os_atomic_t os_atomic_or(os_atomic_t *addr, uint32_t value);
os_atomic_t os_atomic_and(os_atomic_t *addr, uint32_t value);
os_atomic_t os_atomic_xor(os_atomic_t *addr, uint32_t value);
os_atomic_t os_atomic_nand(os_atomic_t *addr, uint32_t value);
os_atomic_t os_atomic_load(const os_atomic_t *addr);
void os_atomic_store(os_atomic_t* addr, uint32_t value);
os_atomic_t os_atomic_exchange(os_atomic_t* addr, uint32_t value);

#endif //ATOMIC_H
