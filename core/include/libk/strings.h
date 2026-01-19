#pragma once

#include <stdint.h>
#include <stddef.h>

void* memset(void* dest, uint8_t value, size_t size);
void* memcpy(void* dest, const void* src, size_t size);
void* memmove(void *dest, const void *src, size_t size);
int memcmp(const void *s1, const void *s2, size_t size);

int isAlpha(char ch);
char upper(char ch);
char lower(char ch);

int strlen(const char *str);
int strcmp(const char *str1, char *str2);
