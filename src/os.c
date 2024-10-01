#include "os.h"


static const int lookup_table[32] = {
    1, 2, 30, 3, 31, 13, 29, 4,
    20, 31, 17, 14, 19, 7, 12, 22,
    21, 18, 15, 16, 11, 10, 9, 8,
    6, 5, 28, 27, 26, 25, 24, 23
};

// ReSharper disable once CppInconsistentNaming
OS_WEAK int __os_ffs(const unsigned int value) {
    if (value == 0)
    {
        return 0;
    }
    return lookup_table[((value & -value) * 0x077CB531U) >> 27];
}
