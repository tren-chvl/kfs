#include "vga.h"
#include "gdt.h"


void kmain(void);

void kmain(void) 
{
	initGdt();
	print("GDT is done!\n");
	print("CS = ");
	print_hex(read_cs());
	print("\n");
	printk();
}