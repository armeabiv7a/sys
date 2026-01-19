#include <arch/x86_64/isr.h>

intHandler handlers[INT_HANDLERS] = {0};

char* exceptionMsgs[32] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available (No Math Coprocessor)",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Unknown Interrupt (intel reserved)",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
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

void isrRegisterHandler(int num, intHandler handler) {
	if (num < INT_HANDLERS)
		handlers[num] = handler;
}

void isrHandler(registers* regs) {
    if (regs->intNo < 32)
        panic(exceptionMsgs[regs->intNo]);
    else {
        if (handlers[regs->intNo])
            handlers[regs->intNo](regs);
        picSendEoi(regs->intNo - IRQ_BASE);
    }
}
