MBALIGN     equ  1 << 0
MEMINFO     equ  1 << 1
FLAGS       equ  MBALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4

dd MAGIC
dd FLAGS
dd CHECKSUM

section .text
extern KernelMain
global _start

_start:
    mov esp, stackTop
    
    push ebx
    call KernelMain
loop:
    cli
    hlt
    jmp loop

section .data
align 4096

section .bss
align 16

stackBottom:
    resb 16384
stackTop:
