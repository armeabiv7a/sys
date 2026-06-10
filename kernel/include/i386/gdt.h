#pragma once

#include <stdint.h>

typedef struct {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMid;
    uint8_t access;
    uint8_t limitHigh : 4;
    uint8_t flags : 4;
    uint8_t baseHigh;
} __attribute__((packed)) gdtEntry;

typedef struct {
    uint16_t size;
    gdtEntry* addr;
} __attribute__((packed)) gdtPtr;

typedef enum {
    ACCESSED = 1 << 0,
    READ_WRITE = 1 << 1,
    DIR_CONF = 1 << 2,
    EXECUTABLE = 1 << 3,
    TYPE = 1 << 4,
    PRESENT = 1 << 7,

    DPL_RING0 = 0 << 5,
    DPL_RING1 = 1 << 5,
    DPL_RING2 = 2 << 5,
    DPL_RING3 = 3 << 5
} GDT_ACCESS;

typedef enum {
    CODE64 = 1 << 1,
    MODE = 1 << 2,
    GRANULARITY = 1 << 3
} GDT_FLAGS;

void gdtInit();
void gdtSetEntry(int idx, uint32_t base, uint32_t limit,
                GDT_ACCESS access, GDT_FLAGS flags);
