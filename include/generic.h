//
// Created by zhkag on 24-10-1.
//

#ifndef GENERIC_H
#define GENERIC_H

#define GENERIC_NAME(type) \
static __inline char* type##_name(struct type *a) { \
    return a->name; \
}

#define NAME(a) _Generic((a), \
struct os_thread *: os_thread_name,               \
struct os_timer *: os_timer_name          \
)(a)

#endif //GENERIC_H
