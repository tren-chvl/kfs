ENTRY(_start)

SECTIONS
{
	. = 0x00000800;
	.gdt :
	{
		KEEP(*(.gdt))
	}
	. = 0x001000;
	.text :
	{
		*(.text*)
	}
	.rodata :
	{
		*(.rodata*)
	}
	.data :
	{
		*(.data*)
	}
	.bss :
	{
		*(.bss*)
		*(COMMON)
	}
}
