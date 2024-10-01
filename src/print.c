#include <os.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

void uart_write(char c);
void os_print(const char *format) {
    const char *p = format;
    while (*p != '\0') {
        uart_write(*p);
        p++;
    }
}

void os_println(const char *format) {
    os_print(format);
    uart_write('\r');
    uart_write('\n');
}

static size_t int_to_str(int value, char *str, const size_t size) {
    char temp[20];
    size_t pos = 0;
    bool negative = false;

    if (value < 0) {
        negative = true;
        value = -value;
    }

    do {
        if (pos < sizeof(temp)) {
            temp[pos++] = (value % 10) + '0';
        }
        value /= 10;
    } while (value > 0);

    if (negative && pos < sizeof(temp)) {
        temp[pos++] = '-';
    }

    size_t written = 0;
    while (pos > 0 && written < size - 1) {
        str[written++] = temp[--pos];
    }
    return written;
}

static int os_vsnprintf(char *buf, size_t size, const char *fmt, const va_list args){
    size_t i = 0;  // 输出缓冲区的索引
    const char *p = fmt;

    while (*p && i < size - 1) {  // 确保不会超出缓冲区大小
        if (*p == '%' && *(p + 1)) {
            p++;  // 跳过 '%'
            if (*p == 'd') {
                const int num = va_arg(args, int);
                char num_buf[20];
                i += int_to_str(num, &buf[i], size - i);
            } else if (*p == 's') {
                const char *s = va_arg(args, const char *);
                while (*s && i < size - 1) {
                    buf[i++] = *s++;
                }
            } else {
                // 未知格式符号，直接输出
                buf[i++] = *p;
            }
        } else {
            buf[i++] = *p;
        }
        p++;
    }

    buf[i] = '\0';  // 确保字符串终止
    return i;       // 返回写入的字符数
}


static void os_vprint_helper(void (*output_func)(const char*), const char *format, const va_list args) {
    char buffer[256];
    os_vsnprintf(buffer, sizeof(buffer), format, args);
    output_func(buffer);
}

void os_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    os_vprint_helper(os_print, format, args);
    va_end(args);
}

void os_printfln(const char *format, ...) {
    va_list args;
    va_start(args, format);
    os_vprint_helper(os_println, format, args);
    va_end(args);
}
