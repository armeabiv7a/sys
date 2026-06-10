#include <stdint.h>

#include <i386/gdt.h>

static gdtEntry gdt[7];

void gdtSetEntry(int idx, uint32_t base, uint32_t limit, GDT_ACCESS access, GDT_FLAGS flags) {
    gdtEntry* entry = &gdt[idx];

    entry->baseLow  = base & 0xFFFF;
    entry->baseMid  = (base >> 16) & 0xFF;
    entry->baseHigh = (base >> 24) & 0xFF;

    entry->limitLow  = limit & 0xFFFF;
    entry->limitHigh = (limit >> 16) & 0x0F;

    entry->access = (uint8_t)access;
    entry->flags  = (uint8_t)flags;
}

void gdtInit() {
    gdtSetEntry(0, 0, 0, 0, 0);

    gdtSetEntry(1, 0, 0xfffff,
        (PRESENT | DPL_RING0 | TYPE | EXECUTABLE | READ_WRITE | ACCESSED),
        (MODE | GRANULARITY)
    );
    gdtSetEntry(2, 0, 0xfffff,
        (PRESENT | DPL_RING0 | TYPE | READ_WRITE | ACCESSED),
        (MODE | GRANULARITY)
    );

    gdtSetEntry(3, 0, 0xfffff,
        (PRESENT | DPL_RING3 | TYPE | EXECUTABLE | READ_WRITE | ACCESSED),
        (MODE | GRANULARITY)
    );
    gdtSetEntry(4, 0, 0xfffff,
        (PRESENT | DPL_RING3 | TYPE | READ_WRITE | ACCESSED),
        (MODE | GRANULARITY)
    );

    gdtPtr gdtr = {
        .size = sizeof(gdt) - 1,
        .addr = gdt
    };

    __asm__ volatile ("lgdt %0" : : "m"(gdtr));
    __asm__ volatile (
        "ljmp $0x08, $1f\n\t"
        "1:\n\t"
        
        "mov $0x10, %%ax\n\t"
        "mov %%ax, %%ds\n\t"
        "mov %%ax, %%es\n\t"
        "mov %%ax, %%fs\n\t"
        "mov %%ax, %%gs\n\t"
        "mov %%ax, %%ss\n\t"

        : : : "ax", "memory"
    );
}
