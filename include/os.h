#ifndef __KERNEL_OS_H__
#define __KERNEL_OS_H__

#include <stddef.h>
#include <stdint.h>
#include <timer.h>
#include <scheduler.h>
#include <thread.h>
#include <atomic.h>
#include <tick.h>
#include <idle.h>
#include <atomic.h>
#include <irq.h>
#include "print.h"

#define OS_WEAK __attribute__((weak))
#define OS_CLEANUP(ptr) __attribute__((cleanup(ptr)))
#define OS_UNUSED __attribute__((unused))

typedef int (*os_init_fn_t)(void);
#define OS_INIT_EXPORT(fn, level)                                                       \
            __attribute__((used)) const os_init_fn_t __os_init_##fn __attribute__((section(".os_init_fn." level))) = fn

void os_show_version(void);


int __os_ffs(const unsigned int value);

#endif