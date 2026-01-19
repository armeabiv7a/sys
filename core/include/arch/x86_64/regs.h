#pragma once
#include <stdint.h>

typedef struct {
    uint64_t rax, rbx, rcx, rdx, rbp, rdi, rsi, r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t intNo, errCode;
    uint64_t rip, cs, rflags, rsp, ss;
} __attribute__((packed)) registers;
