//
// Created by zhkag on 24-10-1.
//
#include "os.h"
#include "atomic.h"
#include <stdio.h>

OS_WEAK os_atomic_t os_atomic_add(os_atomic_t *addr, const uint32_t value)
{
    return __atomic_fetch_add(addr, value,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_sub(os_atomic_t *addr, const uint32_t value)
{
    return __atomic_fetch_sub(addr, value,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_inc(os_atomic_t *addr)
{
    return __atomic_fetch_add(addr, 1,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_dec(os_atomic_t *addr)
{
    return __atomic_fetch_sub(addr, 1, __ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_inc_return(os_atomic_t *addr)
{
    return __atomic_add_fetch(addr, 1, __ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_dec_return(os_atomic_t *addr)
{
    return __atomic_sub_fetch(addr, 1,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_or(os_atomic_t *addr, const uint32_t value)
{
    return __atomic_fetch_or(addr, value,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_and(os_atomic_t *addr, const uint32_t value)
{
    return __atomic_fetch_and(addr, value,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_xor(os_atomic_t *addr, const uint32_t value)
{
    return __atomic_fetch_xor(addr, value,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_nand(os_atomic_t *addr, const uint32_t value)
{
    return __atomic_fetch_nand(addr, value,__ATOMIC_SEQ_CST);
}
OS_WEAK os_atomic_t os_atomic_load(const os_atomic_t *addr)
{
    return __atomic_load_n(addr, __ATOMIC_SEQ_CST);
}
OS_WEAK void os_atomic_store(os_atomic_t* addr, const uint32_t value)
{
    return __atomic_store_n(addr,value,__ATOMIC_SEQ_CST);
}

OS_WEAK os_atomic_t os_atomic_exchange(os_atomic_t* addr, const uint32_t value)
{
    return __atomic_exchange_n(addr,value,__ATOMIC_SEQ_CST);
}

