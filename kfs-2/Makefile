TARGET = kernel
ISO_DIR = iso
BOOT_DIR = iso/boot
GRUB_DIR = iso/boot/grub

CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -fno-stack-protector -fno-builtin -nostdlib -nodefaultlibs -fno-pic -I.
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

SRC = src/kernel.c src/vga.c src/gdt.c test.c
OBJ = src/boot.o src/gdt.s.o read_gdt.o $(SRC:.c=.o)

all: clean $(TARGET) iso

clean:
	rm -f *.o src/*.o src/gdt.s.o src/boot.o

src/read_gdtr.o: read_gdtr.s
	$(AS) -f elf32 read_gdtr.s -o read_gdtr.o

src/boot.o: src/boot.s
	$(AS) -f elf32 src/boot.s -o src/boot.o

src/gdt.s.o: src/gdt.s
	$(AS) -f elf32 src/gdt.s -o src/gdt.s.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJ)
	cp $(TARGET) $(BOOT_DIR)/kernel

iso:
	mkdir -p $(GRUB_DIR)
	cp grub.cfg $(GRUB_DIR)/
	grub-mkrescue -o kernel.iso iso/
