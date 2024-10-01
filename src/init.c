#include <os.h>
static int board_start(void)
{
    return 0;
}
OS_INIT_EXPORT(board_start, "0");
static int board_end(void)
{
    return 0;
}
OS_INIT_EXPORT(board_end, "0.end");

static int app_start(void)
{
    return 0;
}
OS_INIT_EXPORT(app_start, "5.end");

static int end(void)
{
    return 0;
}
OS_INIT_EXPORT(end, "6.end");

void os_board_init(void)
{
    for (volatile const os_init_fn_t* fn_ptr = &__os_init_board_start; fn_ptr < &__os_init_board_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }
}

static uint8_t test_thread_stack[512];
struct os_thread test_thread;

static int test_thread_entry(void *parameter)
{
    while (1)
    {
        os_println("test_thread_entry");
    }
    // ReSharper disable once CppDFAUnreachableCode
    return 0;
}

static void os_test_init(void)
{
    os_thread_init(&test_thread, "test", test_thread_entry, NULL,
                            test_thread_stack, sizeof(test_thread_stack), 20, 5);
    os_thread_startup(&test_thread);
}


static uint8_t main_thread_stack[512];
struct os_thread main_thread;

#include "timer.h"

#include "mutex.h"

struct os_mutex mutex;

static int main_thread_entry(void *parameter)
{
    for (volatile const os_init_fn_t* fn_ptr = &__os_init_app_start; fn_ptr < &__os_init_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }

    os_mutex_init(&mutex);
    os_mutex_lock(&mutex);
    os_mutex_unlock(&mutex);
    os_mutex_lock(&mutex);
    os_mutex_lock(&mutex);
    os_test_init();
    os_printfln("name: %s\n", NAME(&main_thread));
    while (1)
    {
        os_println("main_thread_entry");
    }
    // ReSharper disable once CppDFAUnreachableCode
    return 0;
}

static void os_main_init(void)
{
    os_thread_init(&main_thread, "main", main_thread_entry, NULL,
                            main_thread_stack, sizeof(main_thread_stack), 20, 5);
    os_thread_startup(&main_thread);
}


int entry(void)
{
    OS_IRQ_DISABLE
    os_board_init();
    OS_PRINT_CLEAR();
    os_show_version();
    os_scheduler_init();
    os_main_init();
    os_idle_init();
    os_scheduler_start();
    return 0;
}
