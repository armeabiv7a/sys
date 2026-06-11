#include <stdint.h>

#include <i386/gdt.h>

static gdtEntry gdt[7];

void gdtSetEntry(int idx, uint32_t base, uint32_t limit, GDT_ACCESS access, GDT_FLAGS flags) {
    gdtEntry* entry = &gdt[idx];

    entry->baseLow  = base & 0xffff;
    entry->baseMid  = (base >> 16) & 0xff;
    entry->baseHigh = (base >> 24) & 0xff;

    entry->limitLow  = limit & 0xffff;
    entry->limitHigh = (limit >> 16) & 0x0f;

    entry->access = (uint8_t)access;
    entry->flags  = (uint8_t)flags;
}

void gdtInit() {
    gdtSetEntry(0, 0, 0, 0, 0);

    gdtSetEntry(1, 0, 0xfffff,
        (GDT_PRESENT | GDT_DPL_RING0 | GDT_TYPE | GDT_EXECUTABLE | GDT_READ_WRITE | GDT_ACCESSED),
        (GDT_MODE | GDT_GRANULARITY)
    );
    gdtSetEntry(2, 0, 0xfffff,
        (GDT_PRESENT | GDT_DPL_RING0 | GDT_TYPE | GDT_READ_WRITE | GDT_ACCESSED),
        (GDT_MODE | GDT_GRANULARITY)
    );

    gdtSetEntry(3, 0, 0xfffff,
        (GDT_PRESENT | GDT_DPL_RING3 | GDT_TYPE | GDT_EXECUTABLE | GDT_READ_WRITE | GDT_ACCESSED),
        (GDT_MODE | GDT_GRANULARITY)
    );
    gdtSetEntry(4, 0, 0xfffff,
        (GDT_PRESENT | GDT_DPL_RING3 | GDT_TYPE | GDT_READ_WRITE | GDT_ACCESSED),
        (GDT_MODE | GDT_GRANULARITY)
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
