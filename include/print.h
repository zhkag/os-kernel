//
// Created by zhkag on 24-10-1.
//

#ifndef PRINT_H
#define PRINT_H

// 显示方式宏
#define PRINT_DISPLAY_DEFAULT      "0"  // 默认值
#define PRINT_DISPLAY_BOLD         "1"  // 高亮（粗体）
#define PRINT_DISPLAY_NO_BOLD      "22" // 非粗体
#define PRINT_DISPLAY_UNDERLINE    "4"  // 下划线
#define PRINT_DISPLAY_NO_UNDERLINE "24" // 非下划线
#define PRINT_DISPLAY_BLINK        "5"  // 闪烁
#define PRINT_DISPLAY_NO_BLINK     "25" // 非闪烁
#define PRINT_DISPLAY_INVERT       "7"  // 反显
#define PRINT_DISPLAY_NO_INVERT    "27" // 非反显


// 字体颜色宏
#define PRINT_FONT_BLACK     "30"       // 黑色字体
#define PRINT_FONT_RED       "31"       // 红色字体
#define PRINT_FONT_GREEN     "32"       // 绿色字体
#define PRINT_FONT_YELLOW    "33"       // 黄色字体
#define PRINT_FONT_BLUE      "34"       // 蓝色字体
#define PRINT_FONT_PURPLE    "35"       // 紫色字体
#define PRINT_FONT_CYAN      "36"       // 青色字体
#define PRINT_FONT_WHITE     "37"       // 白色字体

// 背景颜色宏
#define PRINT_BACKGROUND_BLACK    "40"  // 黑色背景
#define PRINT_BACKGROUND_RED      "41"  // 红色背景
#define PRINT_BACKGROUND_GREEN    "42"  // 绿色背景
#define PRINT_BACKGROUND_YELLOW   "43"  // 黄色背景
#define PRINT_BACKGROUND_BLUE     "44"  // 蓝色背景
#define PRINT_BACKGROUND_PURPLE   "45"  // 紫色背景
#define PRINT_BACKGROUND_CYAN     "46"  // 青色背景
#define PRINT_BACKGROUND_WHITE    "47"  // 白色背景

// 光标控制与屏幕操作宏
#define PRINT_CURSOR_UP(n)       #n "A"   // 光标上移 n 行
#define PRINT_CURSOR_DOWN(n)     #n "B"   // 光标下移 n 行
#define PRINT_CURSOR_RIGHT(n)    #n "C"   // 光标右移 n 行
#define PRINT_CURSOR_LEFT(n)     #n "D"   // 光标左移 n 行
#define PRINT_CURSOR_POSITION(y, x) #y ";" #x "H"  // 设置光标位置 (y, x)

#define PRINT_CLEAR_SCREEN       "2J"        // 清屏
#define PRINT_CLEAR_LINE         "K"         // 清除从光标到行尾的内容

#define PRINT_SAVE_CURSOR        "s"         // 保存光标位置
#define PRINT_RESTORE_CURSOR     "u"         // 恢复光标位置

#define PRINT_HIDE_CURSOR        "?25l"      // 隐藏光标
#define PRINT_SHOW_CURSOR        "?25h"      // 显示光标



void os_print(const char *format);
void os_println(const char *format);
void os_printf(const char *format, ...);
void os_printfln(const char *format, ...);

#define OS_PRINT_SET(set) os_print("\033[" set)
#define OS_PRINT_SET_M(m) OS_PRINT_SET(m "m")
#define OS_PRINT_CLEAR() os_print("\033[0m");

void os_print(const char *format);
void os_println(const char *format);
void os_printf(const char *format, ...);
void os_printfln(const char *format, ...);

#define OS_PRINTF_DEBUG(format, ...) \
os_printf("%s:%d:%s: " format "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define OS_PRINT_DEBUG(format, ...) \
os_printfln("%s:%d:%s: " format "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#endif //PRINT_H
