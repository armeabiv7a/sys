#pragma once
#include <stdint.h>

typedef struct {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t  baseMid;
    uint8_t  access;
    uint8_t  flags;
    uint8_t  baseHigh;
} __attribute__((packed)) GdtEntry;

typedef struct {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t  baseMid1;
    uint8_t  access;
    uint8_t  flags;
    uint8_t  baseMid2;
    uint32_t baseHigh;
    uint32_t reserved;
} __attribute__((packed)) GdtTssEntry;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) GdtPtr;

typedef struct {
    uint32_t reserved0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved1;
    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t reserved2;
    uint16_t reserved3;
    uint16_t iomapBase;
} __attribute__((packed)) Tss64;

void InitGdt();
