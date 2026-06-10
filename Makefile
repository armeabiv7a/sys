ASM = nasm
CC = x86_64-elf-gcc
LD = x86_64-elf-ld
GRUB = grub-mkrescue
QEMU = qemu-system-x86_64

KERNEL = kernel
SRC = $(KERNEL)/src
INC = $(KERNEL)/include
OUT = build

ASM_FLAGS = -f elf32
CC_FLAGS = -I$(INC) -m32 -std=gnu99 -ffreestanding -Wall -Wextra
LD_FLAGS = -m elf_i386 -T $(KERNEL)/linker.ld -nostdlib

MKDIR = mkdir -p
RMDIR = rm -rf
CP = cp -f

TARGET = $(OUT)/kernel.bin
ISO = $(OUT)/kernel.iso
ISO_DIR = $(OUT)/iso

C_FILES = $(shell find $(SRC) -type f -name "*.c")
ASM_FILES = $(shell find $(SRC) -type f -name "*.asm")
OBJS = $(patsubst $(SRC)/%.asm, $(OUT)/%.o, $(ASM_FILES)) $(patsubst $(SRC)/%.c, $(OUT)/%.o, $(C_FILES))

.PHONY: all run clean

all: $(TARGET) run clean

$(TARGET): $(OBJS)
	@$(LD) $(LD_FLAGS) -o $(TARGET) $(OBJS)
	@$(MKDIR) $(ISO_DIR)/boot/grub
	@$(CP) $(TARGET) $(ISO_DIR)/boot/
	@$(CP) $(KERNEL)/grub.cfg $(ISO_DIR)/boot/grub/
	@$(GRUB) -o $(ISO) $(ISO_DIR) -- -report_about warning

$(OUT)/%.o: $(SRC)/%.c | $(OUT)
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c -o $@ $<

$(OUT)/%.o: $(SRC)/%.asm | $(OUT)
	@mkdir -p $(dir $@)
	@$(ASM) $(ASM_FLAGS) -o $@ $<

$(OUT):
	@$(MKDIR) $(OUT)

run:
	@$(QEMU) -drive format=raw,file=$(ISO)

clean:
	@$(RMDIR) $(OUT)
