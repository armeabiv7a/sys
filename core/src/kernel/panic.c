#include <kernel/panic.h>

void panic(char* msg) {
    cliCpu();
    clearScr(0xffffff);
    write(0, 0, 0xff0000, "PANIC:");
    write(0, 20, 0x000000, msg);
    while(1) haltCpu();
}
