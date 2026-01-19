#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <libk/strings.h>
#include <arch/x86_64/cpu.h>

void write(int x, int y, uint32_t color, char* str);
void drawBitmap(int x, int y, int width, int height, uint32_t* data);
void drawChar(int x, int y, int width, int height, uint32_t color, uint8_t* ch);
void clearScr(uint32_t color);
void drawPixel(uint64_t x, uint64_t y, uint32_t color);
void InitVga(volatile struct limine_framebuffer_request fbRequest);
