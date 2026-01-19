#!/bin/bash
set -e

CC=gcc
LD=ld
NASM=nasm

BOOT_DIR=boot
SRC_DIR=core/src
BUILD_DIR=out
ISO_ROOT=$BUILD_DIR/iso

CFLAGS="-g -O2 -pipe -Wall -Wextra -Wno-attributes -std=gnu11 -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -fno-PIC -ffunction-sections -fdata-sections -m64 -march=x86-64 -mabi=sysv -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel -Icore/include"
NASMFLAGS="-f elf64 -Wall"
LDFLAGS="-m elf_x86_64 -nostdlib -static -z max-page-size=0x1000 --gc-sections -T $SRC_DIR/linker.ld"

mkdir -p $BUILD_DIR
OBJ=""

echo "[*] Компиляция..."

for f in $(find $SRC_DIR -type f); do
    case "$f" in
        *.c)
            out="$BUILD_DIR/$(basename "$f" .c).o"
            echo "  GCC: $f"
            $CC $CFLAGS -c "$f" -o "$out"
            OBJ="$OBJ $out"
            ;;
        *.asm)
            out="$BUILD_DIR/$(basename "$f" .asm).o"
            echo "  NASM: $f"
            $NASM $NASMFLAGS "$f" -o "$out"
            OBJ="$OBJ $out"
            ;;
    esac
done

echo "[*] Линковка..."
$LD $LDFLAGS -o $BUILD_DIR/kernel.elf $OBJ
echo "[✔] Готово: $BUILD_DIR/kernel.elf"


mkdir -p $ISO_ROOT/limine
cp -v $BUILD_DIR/kernel.elf $ISO_ROOT
cp -v $BOOT_DIR/limine.conf $BOOT_DIR/bin/limine-bios.sys $BOOT_DIR/bin/limine-bios-cd.bin \
      $BOOT_DIR/bin/limine-uefi-cd.bin $ISO_ROOT/limine/

mkdir -p $ISO_ROOT/EFI/BOOT
cp -v $BOOT_DIR/bin/BOOTX64.EFI $ISO_ROOT/EFI/BOOT
cp -v $BOOT_DIR/bin/BOOTIA32.EFI $ISO_ROOT/EFI/BOOT

echo "[*] Создание ISO образа..."
xorriso -as mkisofs -R -r -J -b limine/limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
        -apm-block-size 2048 --efi-boot limine/limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        $ISO_ROOT -o $ISO_ROOT/image.iso

limine bios-install $ISO_ROOT/image.iso
echo "[✔] Готово: image.iso"

qemu-system-x86_64 -cdrom $ISO_ROOT/image.iso -m 512M -smp 2 -net none -rtc base=utc

rm -rf $BUILD_DIR
