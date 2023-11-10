ENTRY(Reset_Handler)

MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 524288  /* 0x0808.0000 */
	RESULT(rwx): ORIGIN = 0x20000000, LENGTH = 4       /* 0x2000.0004*/
	SRAM  (rwx): ORIGIN = 0x20000004, LENGTH = 131068  /* 0x2002.0000 */
}

SECTIONS 
{
	.text :
	{
		*(.isr_vector)
		*(.text)
			*(.rodata)
			. = ALIGN(4);
			_etext = .;
	}> FLASH
	
	_la_data = LOADADDR(.data);
  
	.data :
	{
		_sdata = .;
			*(.data)
			. = ALIGN(4);
			_edata = .;
	}> SRAM AT> FLASH

	.bss :
	{
		_sbss = .;
			*(.bss)
			. = ALIGN(4);
			_ebss = .;
	}> SRAM
	
	.result :
	{
		*(.result)
	}> RESULT
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);
