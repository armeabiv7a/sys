section .text
extern intHandler

%macro ISR_NOERR 1
global isr%1
isr%1:
    cli
    push dword 0
    push dword %1
    jmp isrCommon
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
    cli
    push dword %1
    jmp isrCommon
%endmacro

%assign i 0
%rep 256
    %if i == 8 || (i >= 10 && i <= 14) || i == 17 || i == 21 || i == 29 || i == 30
        ISR_ERR i
    %else
        ISR_NOERR i
    %endif
%assign i i+1
%endrep

isrCommon:
    pushad

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call intHandler
    add esp, 4

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad
    add esp, 8
    
    iret

section .rodata
global isrHandlers
isrHandlers:
	%assign i 0
	%rep 256
	dd isr%+ i
	%assign i i + 1
	%endrep
