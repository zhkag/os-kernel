//
// Created by zhkag on 24-10-1.
//

#include "mutex.h"

#include <scheduler.h>


void os_mutex_init(struct os_mutex * mutex)
{
    os_list_init(&mutex->thread_list);
    mutex->owner_thread = os_thread_self();
    mutex->recursion_count = 0;
    os_atomic_store(&mutex->lock,0);
}

void os_mutex_lock(struct os_mutex * mutex)
{
    struct os_thread * thread = os_thread_self();
    if (!os_atomic_exchange(&mutex->lock, 1)) {
        //没有其他线程占用，直接成为互斥量主线程
        mutex->owner_thread = thread;
        mutex->recursion_count = 1;
        mutex->priority = thread->current_priority;
    }else{
        // 已经有线程占用锁，先判断是不是自己占用
        if (mutex->owner_thread == thread)
        {   // 是自己占用，计数加
            mutex->recursion_count++;
        }
        else
        {   // 非自己占用，挂起线程，等待互斥量主线程释放
            thread->stat = thread_suspend;
            if (thread->current_priority < mutex->owner_thread->current_priority)
            {
                os_thread_set_priority(mutex->owner_thread, thread->current_priority);
            }
            os_list_insert_after(&mutex->thread_list, &thread->list);
        }
    }
}

void os_mutex_unlock(struct os_mutex * mutex)
{
    mutex->recursion_count--;
    if (mutex->recursion_count == 0)
    {
        if (mutex->owner_thread->current_priority < mutex->priority)
        {
            os_thread_set_priority(mutex->owner_thread, mutex->priority); //将修改的优先级设置回来
        }
        if (os_list_is_empty(&mutex->thread_list))
        {
            mutex->owner_thread = NULL;
            os_atomic_store(&mutex->lock,0);
        }
        // 判断还有没有线程要持有锁，如果有则持有，如果没有则退出
    }
}