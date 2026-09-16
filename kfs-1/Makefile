CC      = gcc
AS      = nasm
LD      = ld
GRUBMK  = grub-mkrescue
QEMU    = qemu-system-i386

CFLAGS  = -m32 -fno-stack-protector -fno-builtin -ffreestanding
LDFLAGS = -m elf_i386 -T linker.ld

KERNEL  = kernel.bin
ISO     = kernel.iso

.PHONY: all iso run clean

all: $(ISO)

$(KERNEL): boot.o kernel.o vga.o linker.ld
	$(LD) $(LDFLAGS) -o $@ boot.o kernel.o vga.o

boot.o: boot.s
	$(AS) -f elf32 $< -o $@

kernel.o: kernel.c vga.h stdint.h
	$(CC) $(CFLAGS) -c $< -o $@

vga.o: vga.c vga.h stdint.h
	$(CC) $(CFLAGS) -c $< -o $@

iso: $(ISO)

$(ISO): $(KERNEL) iso/boot/grub/grub.cfg
	cp $(KERNEL) iso/boot/kernel
	$(GRUBMK) \
		--install-modules="multiboot" \
		--locales="" \
		--fonts="" \
		--themes="" \
		-o $@ \
		iso

run: $(ISO)
	$(QEMU) -cdrom $(ISO)

clean:
	rm -f boot.o kernel.o vga.o $(KERNEL) $(ISO)