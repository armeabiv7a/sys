#include <arch/x86_64/gdt.h>

static struct {
    GdtEntry null;
    GdtEntry code;
    GdtEntry data;
    GdtTssEntry tss;
} __attribute__((packed)) gdt;

static GdtPtr gdtPtr;
static Tss64 tss;

static GdtEntry codeSegDesc (void) {
    return (GdtEntry){
        .limitLow = 0xFFFF,
        .baseLow = 0x0000,
        .baseMid = 0x00,
        .access = 0x9A,
        .flags = 0xA0,
        .baseHigh = 0x00 };
} static GdtEntry dataSegDesc (void) {
    return (GdtEntry){
        .limitLow = 0xFFFF,
        .baseLow = 0x0000,
        .baseMid = 0x00,
        .access = 0x92,
        .flags = 0x80,
        .baseHigh = 0x00 };
} static GdtTssEntry tssDesc (uint64_t base, uint32_t limit) {
    return (GdtTssEntry){
        .limitLow = limit & 0xFFFF,
        .baseLow  = base & 0xFFFF,
        .baseMid1 = (base >> 16) & 0xFF,
        .access    = 0x89,
        .flags     = (limit >> 16) & 0x0F,
        .baseMid2 = (base >> 24) & 0xFF,
        .baseHigh = (base >> 32),
        .reserved  = 0 };
}

void InitGdt() {
    gdt.null = (GdtEntry){0};
    gdt.code = codeSegDesc();
    gdt.data = dataSegDesc();

    tss = (Tss64){0};
    tss.rsp0 = 0x0;
    tss.iomapBase = sizeof(Tss64);

    gdt.tss = tssDesc((uint64_t)&tss, sizeof(Tss64) - 1);

    gdtPtr.limit = sizeof(gdt) - 1;
    gdtPtr.base = (uint64_t)&gdt;

    asm volatile ("lgdt %0" : : "m"(gdtPtr));
    
    reloadSegments();

    uint16_t tssSelector = (sizeof(GdtEntry) * 3);
    asm volatile ("ltr %0": : "r"(tssSelector));
}
