#include <os.h>
void os_show_version(void)
{
    // os.println("");
    os_println("");
    os_printfln("%d.%d.%d build %s %s",
               0, 0, 0, __DATE__, __TIME__);
}
