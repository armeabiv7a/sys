#pragma once

#include <stdint.h>

#define IDT_ENTRIES 256
#define KERNEL_CS 0x08

#define PIC1_DATA    0x21
#define PIC2_DATA    0xA1

typedef struct {
    uint16_t baseLow;
    uint16_t selector;
    uint8_t reserved;
    uint8_t attrs;
    uint16_t baseHigh;
} __attribute__((packed)) idtEntry;

typedef struct {
    uint16_t size;
    idtEntry* addr;
} __attribute__((packed)) idtPtr;

typedef enum {
    IDT_TASK_GATE = 0x5,
    IDT_INT_GATE16 = 0x6,
    IDT_TRAP_GATE16 = 0x7,
    IDT_INT_GATE32 = 0xe,
    IDT_TRAP_GATE32 = 0xf,

    IDT_DPL_RING0 = 0 << 5,
    IDT_DPL_RING1 = 1 << 5,
    IDT_DPL_RING2 = 2 << 5,
    IDT_DPL_RING3 = 3 << 5,

    IDT_PRESENT = 1 << 7
} IDT_ATTRS;

extern void* isrHandlers[IDT_ENTRIES];

void intInit();
void idtSetEntry(int idx, void* isr, uint16_t selector, IDT_ATTRS attrs);
