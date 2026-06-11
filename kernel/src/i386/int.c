#include <stdint.h>
#include <print.h>

#include <i386/int.h>
#include <i386/cpu.h>

static idtEntry idt[IDT_ENTRIES];
const char* exceptions[32] = {
    "Divide By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FPU Floating-Point Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception"
};

void idtSetEntry(int idx, void* isr, uint16_t selector, IDT_ATTRS attrs) {
    idtEntry* entry = &idt[idx];
    uint32_t base = (uint32_t)isr;

    entry->baseLow = base & 0xffff;
    entry->baseHigh = (base >> 16) & 0xffff;
    entry->selector = selector;
    entry->attrs = (uint8_t)attrs;
    entry->reserved = 0;
}

void intHandler(Regs* regs) {
    printdbg("Exception: ");
    printdbg((char*)exceptions[regs->intNo]);
    while(1) __asm__ volatile ("hlt");
}

void intInit() {
    for (int i = 0; i < 32; i++) {
        idtSetEntry(i, isrHandlers[i], KERNEL_CS, IDT_PRESENT | IDT_INT_GATE32);
    }

    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    idtPtr idtr = {
        .size = sizeof(idt) - 1,
        .addr = idt
    };

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}
