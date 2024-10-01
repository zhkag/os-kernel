//
// Created by zhkag on 24-10-1.
//

#ifndef OS_THREAD_H
#define OS_THREAD_H

#include <stdint.h>
#include <string.h>
#include <list.h>
#include <atomic.h>
#include <generic.h>
#include <timer.h>

//
// 1. 初始化 initialization
// 2. 挂起 Suspend
// 3. 就绪 ready
// 4. 运行 Running
// 5. 终止 terminate

enum os_thread_state
{
    thread_initialization,  // 初始化
    thread_suspend,         // 挂起
    thread_ready,           // 就绪
    thread_running,         // 运行
    thread_terminate,       // 终止
};

struct os_thread
{
    char        name[8];                      /**< the name of thread */
    uint8_t  flags;                                  /**< thread's flags */
    void       *sp;                                     /**< stack point */
    int         (*entry)(void *parameter);                                  /**< entry */
    void       *parameter;                              /**< parameter */
    void       *stack_addr;                             /**< stack address */
    uint32_t stack_size;                             /**< stack size */

    uint32_t    error;                                  /**< error code */

    uint8_t  stat:3;                                   /**< thread status */

    uint8_t  init_priority;                       /**< current priority */
    uint8_t  current_priority;                       /**< current priority */

    // uint32_t number_mask;

    os_atomic_t init_tick;
    os_atomic_t remaining_tick;

    struct os_list list;
    struct os_list all_list;
    struct os_timer timer;


};

uint8_t *os_stack_init(void       *entry,
                          void       *parameter,
                          uint8_t *stack_addr,
                          void       *exit);
uint32_t os_thread_init(struct os_thread *thread,
                        const char       *name,
                        int (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        uint32_t       stack_size,
                        uint8_t        priority,
                        uint32_t       tick);
uint32_t os_thread_startup(struct os_thread *thread);

uint32_t os_thread_set_priority(struct os_thread *thread, const uint8_t priority);

GENERIC_NAME(os_thread)


#endif //OS_THREAD_H
