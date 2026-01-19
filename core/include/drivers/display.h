#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <libk/strings.h>
#include <arch/x86_64/cpu.h>

typedef struct {
    int x;
    int y;
} vgaPos;

void write(char* str);
void drawBitmap(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t* data);
void clearScr(uint32_t color);
void drawChar(char ch, uint64_t x, uint64_t y, uint32_t color);
void drawPixel(uint64_t x, uint64_t y, uint32_t color);
void setPos(vgaPos cords);
vgaPos getPos();
void InitVga(volatile struct limine_framebuffer_request fbRequest);
