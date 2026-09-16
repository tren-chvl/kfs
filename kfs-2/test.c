#include "stdint.h"
#include "vga.h"
#include "gdt.h"
void read_gdtr(uint64_t *gdtr);

uint16_t read_cs()
{
	uint16_t cs;
	asm volatile ("mov %%cs, %0" : "=r"(cs));
	return cs;
}

