#pragma once
#include <stdint.h>

typedef struct {
    uint64_t r15, r14, r13, r12, rbp, rbx;
    uint64_t r11, r10, r9, r8, rax, rcx, rdx, rsi, rdi;
    uint64_t intNo, errCode;
    uint64_t rip, cs, eflags, rsp, ss;
} __attribute__((packed)) registers;
