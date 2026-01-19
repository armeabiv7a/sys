#include <arch/x86_64/idt.h>

IdtEntry idt[IDT_ENTRIES];
IdtPtr idtPtr;

void idtSetEntry(int index, intHandler handler) {
    IdtEntry* this = &idt[index];
    uint64_t base = (uint64_t)handler;

    this->offsetLow = (uint16_t)(base & 0xFFFF);
    this->offsetMid = (uint16_t)((base >> 16) & 0xFFFF);
    this->offsetHigh = (uint32_t)((base >> 32) & 0xFFFFFFFF);
    this->selector = KERNEL_CS;
    this->flags = INT_ATTR;
    this->ist = 0;
    this->zero = 0;
}

void InitIdt() {
    idtPtr.base = (uint64_t)&idt;
    idtPtr.limit = sizeof(idt) - 1;
    InitPic();

    idtSetEntry(0, isr0);
    idtSetEntry(1, isr1);
    idtSetEntry(2, isr2);
    idtSetEntry(3, isr3);
    idtSetEntry(4, isr4);
    idtSetEntry(5, isr5);
    idtSetEntry(6, isr6);
    idtSetEntry(7, isr7);
    idtSetEntry(8, isr8);
    idtSetEntry(9, isr9);
    idtSetEntry(10, isr10);
    idtSetEntry(11, isr11);
    idtSetEntry(12, isr12);
    idtSetEntry(13, isr13);
    idtSetEntry(14, isr14);
    idtSetEntry(15, isr15);
    idtSetEntry(16, isr16);
    idtSetEntry(17, isr17);
    idtSetEntry(18, isr18);
    idtSetEntry(19, isr19);
    idtSetEntry(20, isr20);
    idtSetEntry(21, isr21);
    idtSetEntry(22, isr22);
    idtSetEntry(23, isr23);
    idtSetEntry(24, isr24);
    idtSetEntry(25, isr25);
    idtSetEntry(26, isr26);
    idtSetEntry(27, isr27);
    idtSetEntry(28, isr28);
    idtSetEntry(29, isr29);
    idtSetEntry(30, isr30);
    idtSetEntry(31, isr31);
    idtSetEntry(32, irq0);
    idtSetEntry(33, irq1);
    idtSetEntry(34, irq2);
    idtSetEntry(35, irq3);
    idtSetEntry(36, irq4);
    idtSetEntry(37, irq5);
    idtSetEntry(38, irq6);
    idtSetEntry(39, irq7);
    idtSetEntry(40, irq8);
    idtSetEntry(41, irq9);
    idtSetEntry(42, irq10);
    idtSetEntry(43, irq11);
    idtSetEntry(44, irq12);
    idtSetEntry(45, irq13);
    idtSetEntry(46, irq14);
    idtSetEntry(47, irq15);

    asm volatile ("lidt %0" : : "m"(idtPtr));
    stiCpu();
}
