#pragma once
#include <stdint.h>
#include <arch/x86_64/regs.h>
#include <arch/x86_64/pic.h>
#include <kernel/panic.h>

#define INT_HANDLERS       256

typedef void (*intHandler)(registers *);

void isrRegisterHandler(int num, intHandler handler);
void isrHandler(registers* regs);
void irqHandler(registers* regs);

#define IRQ_BASE            0x20
#define IRQ0_TIMER          0x00
#define IRQ1_KEYBOARD       0x01
#define IRQ2_CASCADE        0x02
#define IRQ3_SERIAL_PORT2   0x03
#define IRQ4_SERIAL_PORT1   0x04
#define IRQ5_RESERVED       0x05
#define IRQ6_DISKETTE_DRIVE 0x06
#define IRQ7_PARALLEL_PORT  0x07
#define IRQ8_CMOS_CLOCK     0x08
#define IRQ9_CGA            0x09
#define IRQ10_RESERVED      0x0A
#define IRQ11_RESERVED      0x0B
#define IRQ12_AUXILIARY     0x0C
#define IRQ13_FPU           0x0D
#define IRQ14_HARD_DISK     0x0E
#define IRQ15_RESERVED      0x0F
