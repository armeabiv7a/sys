#include <arch/x86_64/isr.h>

intHandler handlers[INT_HANDLERS];

char* exceptionMsgs[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

static void memHandler(registers* regs) {
	if (handlers[regs->intNo]) {
		intHandler handler = handlers[regs->intNo];
		handler(regs);
	}
}

void isrHandler(registers* regs) {
    memHandler(regs);
	panic(exceptionMsgs[regs->intNo]);
}

void irqHandler(registers* regs) {
    uint8_t irq = regs->intNo - 32;
    memHandler(regs);
	picSendEoi(irq);
}

void isrRegisterHandler(int num, intHandler handler) {
	if (num < INT_HANDLERS)
		handlers[num] = handler;
}
