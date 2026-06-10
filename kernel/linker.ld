
/* Linker script for a 32-bit i386 kernel
	 - Output format: ELF32 (i386)
	 - Entry point: _start
	 - Linked load address: 0x00100000 (1 MiB)
	 - Exports useful symbols: __text_start, __text_end, __data_start, __data_end,
		 __bss_start, __bss_end, _end, _kernel_start
*/

OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
	. = 0x00100000;

	.text ALIGN(0x1000) :
	{
		PROVIDE(__text_start = .);
		*(.multiboot)
		*(.text .text.*)
		*(.rodata .rodata.*)
		PROVIDE(__text_end = .);
	}

	.data ALIGN(0x1000) :
	{
		PROVIDE(__data_start = .);
		*(.data .data.*)
		PROVIDE(__data_end = .);
	}

    .rodata ALIGN(0x1000) :
	{
		PROVIDE(__rodata_start = .);
		*(.rodata .rodata.*)
		PROVIDE(__rodata_end = .);
	}

	.bss ALIGN(0x1000) (NOLOAD) :
	{
		PROVIDE(__bss_start = .);
		*(.bss .bss.*)
		*(COMMON)
		PROVIDE(__bss_end = .);
	}

	PROVIDE(_kernel_start = 0x00100000);
	PROVIDE(_kernel_end = .);
	PROVIDE(_end = .);

	/DISCARD/ : { *(.eh_frame) }
}
