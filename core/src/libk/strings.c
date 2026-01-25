#include <libk/strings.h>

void* memset(void* dest, uint8_t value, size_t size) {
    uint8_t* ptr = (uint8_t*) dest;
    for (; size != 0; size--) *ptr++ = value;
    return dest;
}

void *memcpy(void *dest, const void* src, size_t size) {
    uint8_t* ret = dest;
    uint8_t *p = dest;
    const uint8_t *q = src;
    while (size--)
        *p++ = *q++;
    return ret;
}

void *memmove(void *dest, const void *src, size_t size) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest) {
        for (size_t i = 0; i < size; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        for (size_t i = size; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t size) {
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < size; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

int isAlpha(char ch) {
    return (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')));
}

char upper(char ch) {
    if ((ch >= 'a') && (ch <= 'z'))
        return (ch - 32);
    return ch;
}

char lower(char ch) {
    if ((ch >= 'A') && (ch <= 'Z'))
        return (ch + 32);
    return ch;
}

int strlen(const char *str) {
    int len = 0;
    while (*str++)
        len++;
    return len;
}

int strcmp(const char *str1, char *str2) {
    int i = 0;
    while ((str1[i] == str2[i])) {
        if (str2[i++] == 0)
            return 0;
    }
    return 1;
}

char* itoa(int64_t value, char *str, int base) {
    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    int i = 0;
    char buff[65];
    bool isNegative = (value < 0);
    if (isNegative) value = -value;

    while (value > 0) {
        int64_t rem = value % base;
        buff[i++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
        value /= base;
    }

    if (isNegative) buff[i++] = '-';
    if (base == 16) {
        buff[i++] = 'x';
        buff[i++] = '0';
    }

    int j = 0;
    while (i > 0) str[j++] = buff[--i];
    
    str[j] = '\0';
    return str;
}
