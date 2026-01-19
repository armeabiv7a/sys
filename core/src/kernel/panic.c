#include <kernel/panic.h>

void panic(char* msg) {
    cliCpu();
    clearScr(0xffffff);
    write("PANIC:\n");
    write(msg);
    while(1) haltCpu();
}
