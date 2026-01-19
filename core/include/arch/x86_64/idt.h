#pragma once
#include <stdint.h>
#include <arch/x86_64/regs.h>
#include <arch/x86_64/isr.h>
#include <arch/x86_64/cpu.h>

#define KERNEL_CS 0x08
#define INT_ATTR 0x8E
#define IDT_ENTRIES 256

typedef struct {
    uint16_t offsetLow;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offsetMid;
    uint32_t offsetHigh;
    uint32_t zero;
} __attribute__((packed)) IdtEntry;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) IdtPtr;

typedef registers* (*intHandler)(registers *);

void idtSetEntry(int index, intHandler handler);
void InitIdt();
