#include <arch/x86_64/idt.h>

IdtEntry idt[IDT_ENTRIES];
IdtPtr idtPtr;

void idtSetEntry(int index, uint64_t handler) {
    IdtEntry* this = &idt[index];

    this->offsetLow = (uint16_t)(handler & 0xFFFF);
    this->offsetMid = (uint16_t)((handler >> 16) & 0xFFFF);
    this->offsetHigh = (uint32_t)((handler >> 32) & 0xFFFFFFFF);
    this->selector = KERNEL_CS;
    this->flags = INT_ATTR;
    this->ist = 0;
    this->zero = 0;
}

void InitIdt() {
    idtPtr.base = (uint64_t)&idt;
    idtPtr.limit = sizeof(idt) - 1;
    InitPic();

    idtSetEntry(0, (uint64_t) isr0);
    idtSetEntry(1, (uint64_t) isr1);
    idtSetEntry(2, (uint64_t) isr2);
    idtSetEntry(3, (uint64_t) isr3);
    idtSetEntry(4, (uint64_t) isr4);
    idtSetEntry(5, (uint64_t) isr5);
    idtSetEntry(6, (uint64_t) isr6);
    idtSetEntry(7, (uint64_t) isr7);
    idtSetEntry(8, (uint64_t) isr8);
    idtSetEntry(9, (uint64_t) isr9);
    idtSetEntry(10, (uint64_t) isr10);
    idtSetEntry(11, (uint64_t) isr11);
    idtSetEntry(12, (uint64_t) isr12);
    idtSetEntry(13, (uint64_t) isr13);
    idtSetEntry(14, (uint64_t) isr14);
    idtSetEntry(15, (uint64_t) isr15);
    idtSetEntry(16, (uint64_t) isr16);
    idtSetEntry(17, (uint64_t) isr17);
    idtSetEntry(18, (uint64_t) isr18);
    idtSetEntry(19, (uint64_t) isr19);
    idtSetEntry(20, (uint64_t) isr20);
    idtSetEntry(21, (uint64_t) isr21);
    idtSetEntry(22, (uint64_t) isr22);
    idtSetEntry(23, (uint64_t) isr23);
    idtSetEntry(24, (uint64_t) isr24);
    idtSetEntry(25, (uint64_t) isr25);
    idtSetEntry(26, (uint64_t) isr26);
    idtSetEntry(27, (uint64_t) isr27);
    idtSetEntry(28, (uint64_t) isr28);
    idtSetEntry(29, (uint64_t) isr29);
    idtSetEntry(30, (uint64_t) isr30);
    idtSetEntry(31, (uint64_t) isr31);
    idtSetEntry(32, (uint64_t) irq0);
    idtSetEntry(33, (uint64_t) irq1);
    idtSetEntry(34, (uint64_t) irq2);
    idtSetEntry(35, (uint64_t) irq3);
    idtSetEntry(36, (uint64_t) irq4);
    idtSetEntry(37, (uint64_t) irq5);
    idtSetEntry(38, (uint64_t) irq6);
    idtSetEntry(39, (uint64_t) irq7);
    idtSetEntry(40, (uint64_t) irq8);
    idtSetEntry(41, (uint64_t) irq9);
    idtSetEntry(42, (uint64_t) irq10);
    idtSetEntry(43, (uint64_t) irq11);
    idtSetEntry(44, (uint64_t) irq12);
    idtSetEntry(45, (uint64_t) irq13);
    idtSetEntry(46, (uint64_t) irq14);
    idtSetEntry(47, (uint64_t) irq15);

    asm volatile ("lidt %0" : : "m"(idtPtr));
    stiCpu();
}
