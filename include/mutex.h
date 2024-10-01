//
// Created by zhkag on 24-10-1.
//

#ifndef MUTEX_H
#define MUTEX_H

#include "atomic.h"
#include "thread.h"
#include "list.h"

struct os_mutex{
    struct os_thread * owner_thread;
    os_atomic_t lock;  // 锁的状态，0 表示解锁，1 表示加锁
    uint8_t recursion_count;
    uint8_t priority;
    struct os_list thread_list;
};

void os_mutex_init(struct os_mutex * mutex);
void os_mutex_lock(struct os_mutex * mutex);
void os_mutex_unlock(struct os_mutex * mutex);

#endif //MUTEX_H
