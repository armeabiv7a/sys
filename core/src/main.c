#include <stdint.h>
#include <limine.h>
#include <drivers/display.h>
#include <drivers/keyboard.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/idt.h>

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request fbRequest = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

void KernelMain()
{
    InitVga(fbRequest);
    InitGdt();
    InitIdt();

    InitKb();
    haltCpu();
}
