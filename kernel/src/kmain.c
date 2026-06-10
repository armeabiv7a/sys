#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Print (temporary)
#include <print.h>

uint8_t* buff = (uint8_t*)0xb8000;
void printdbg(char* str) {
    while(*str) {
        if (*str == '\n') {
            int offset = (int)buff - 0xb8000;
            buff += (80 * 2) - (offset - (offset / 20 * 20));

            str++;
            continue;
        }

        *buff++ = *str++;
        *buff++ = 0x07;
    }
}

char* toString(int value, int base) {
    if (value == 0 && base == 16) return "0x00\0";
    if (value == 0) return "0\0";

    static char str[65];
    size_t ind = 0;

    bool isNegative = (value < 0);
    if (isNegative) value = -value;

    char buff[65];
    while (value > 0) {
        uint8_t tmp = value % base;
        buff[ind++] = (tmp < 10) ? (tmp + '0') : (tmp - 10 + 'A');
        value /= base;
    }

    if (base == 16) {
        buff[ind++] = 'x';
        buff[ind++] = '0';
    } if (isNegative) buff[ind++] = '-';

    size_t i = 0;
    while (ind > 0) str[i++] = buff[--ind];

    str[i] = '\0';
    return str;
}

// Kernel entry
#include <i386/gdt.h>

void KernelMain()
{
    gdtInit();

    while(1);
}
