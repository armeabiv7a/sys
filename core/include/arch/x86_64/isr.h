#pragma once
#include <stdint.h>
#include <arch/x86_64/regs.h>
#include <arch/x86_64/pic.h>
#include <arch/x86_64/idt.h>
#include <kernel/panic.h>

typedef registers* (*intHandler)(registers *);

extern registers* isr0(registers*);
extern registers* isr1(registers*);
extern registers* isr2(registers*);
extern registers* isr3(registers*);
extern registers* isr4(registers*);
extern registers* isr5(registers*);
extern registers* isr6(registers*);
extern registers* isr7(registers*);
extern registers* isr8(registers*);
extern registers* isr9(registers*);
extern registers* isr10(registers*);
extern registers* isr11(registers*);
extern registers* isr12(registers*);
extern registers* isr13(registers*);
extern registers* isr14(registers*);
extern registers* isr15(registers*);
extern registers* isr16(registers*);
extern registers* isr17(registers*);
extern registers* isr18(registers*);
extern registers* isr19(registers*);
extern registers* isr20(registers*);
extern registers* isr21(registers*);
extern registers* isr22(registers*);
extern registers* isr23(registers*);
extern registers* isr24(registers*);
extern registers* isr25(registers*);
extern registers* isr26(registers*);
extern registers* isr27(registers*);
extern registers* isr28(registers*);
extern registers* isr29(registers*);
extern registers* isr30(registers*);
extern registers* isr31(registers*);
extern registers* irq0(registers*);
extern registers* irq1(registers*);
extern registers* irq2(registers*);
extern registers* irq3(registers*);
extern registers* irq4(registers*);
extern registers* irq5(registers*);
extern registers* irq6(registers*);
extern registers* irq7(registers*);
extern registers* irq8(registers*);
extern registers* irq9(registers*);
extern registers* irq10(registers*);
extern registers* irq11(registers*);
extern registers* irq12(registers*);
extern registers* irq13(registers*);
extern registers* irq14(registers*);
extern registers* irq15(registers*);

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
#define INT_HANDLERS       256

void isrHandler(registers* regs);
void irqHandler(registers* regs);
void isrRegisterHandler(int num, intHandler handler);
