#pragma once
#include <stdint.h>
#include <libk/ports.h>

#define PIC1        0x20
#define PIC2        0xA0
#define PIC1_CMD    PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2_CMD    PIC2
#define PIC2_DATA   (PIC2+1)

#define ICW1_INIT   0x10
#define ICW1_ICW4   0x01
#define ICW4_8086   0x01

void InitPic();
void picSendEoi(uint8_t irq);
void picMask(uint8_t irq);
void picUnmask(uint8_t irq);
