#include <stdint.h>
#include <stddef.h>

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
