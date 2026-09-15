#include "gdt.h"
#include "stdint.h"

extern void gdt_flush(addr_t);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;


void initGdt()
{
	gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 5) - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;
	setGdtGate(0,0,0,0,0);
	setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //kernerl code seg
	setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //kernel data seg
	setGdtGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // USER code 
	setGdtGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // USER data

	gdt_flush((uint32_t)&gdt_ptr);
}

void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t acces, uint8_t gran)
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
	gdt_entries[num].limit = (limit & 0xFFFF);
	gdt_entries[num].flags = (limit >> 16) & 0x0F;
	gdt_entries[num].flags |= (gran & 0xF0);

	gdt_entries[num].acces = acces;
}


void dump_stack(void)
{
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));

	print("Dump stack:\n");
	print("ESP = ");
	print_hex(esp);
	print("\n");
	uint32_t *ptr = (uint32_t*)esp;
	for (int i = 0; i < 16; i++) 
	{
		print("  [");
		print_hex((uint32_t)(ptr + i));
		print("] = ");
		print_hex(ptr[i]);
		print("\n");
	}
}



void print_hex(uint32_t value)
{
	const char *hex = "0123456789ABCDEF";
	char buf[11];
	buf[0] = '0';
	buf[1] = 'x';
	for (int i = 0; i < 8; i++) 
		buf[2 + i] = hex[(value >> ((7 - i) * 4)) & 0xF];
	buf[10] = '\0';
	print(buf);
}
