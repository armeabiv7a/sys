#pragma once

static inline void haltCpu() {
    asm volatile ("hlt");
}

static inline void cliCpu() {
    asm volatile ("cli");
}

static inline void stiCpu() {
    asm volatile ("sti");
}
