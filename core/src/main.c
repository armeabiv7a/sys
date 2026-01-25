#include <stdint.h>
#include <limine.h>
#include <libk/strings.h>
#include <drivers/display.h>
#include <drivers/keyboard.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/idt.h>
#include <arch/x86_64/isr.h>
#include <mem/pmm.h>

void KernelMain()
{
    InitVga();
    InitGdt();
    InitIdt();

    InitPmm();
    InitKb();

    while(1)
        haltCpu();
}
