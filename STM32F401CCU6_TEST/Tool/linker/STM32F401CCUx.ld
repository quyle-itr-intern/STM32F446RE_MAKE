/* Entry Point */
ENTRY(Reset_Handler) /* The function named 'Reset_Handler' is defined */
                     /* in the 'startup.s' assembly file.             */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;  /* Required amount of heap  */
_Min_Stack_Size = 0x400; /* Required amount of stack */

/* --------------------------------------------------------------------*/
/*                    MEMORY AREAS                                     */
/* --------------------------------------------------------------------*/
MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 262144  /* 0x0804.0000 256 KBytes */
	RESULT(rwx): ORIGIN = 0x20000000, LENGTH = 4       /* 0x2000.0004 4 Bytes    */
	SRAM  (rwx): ORIGIN = 0x20000004, LENGTH = 65532   /* 0x2001.0000 */
}

/* --------------------------------------------------------------------*/
/*                    OUTPUT SECTIONS                                  */
/* --------------------------------------------------------------------*/
SECTIONS 
{
	/******************************************/
    /*      VECTOR TABLE AND PROGRAM CODE     */
    /******************************************/
	.text :
	{
		*(.isr_vector)
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
	}> FLASH
	
	_la_data = LOADADDR(.data);
  
	/****************************/
    /*    INITIALIZED DATA      */
    /****************************/
	.data :
	{
		_sdata = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;
	}> SRAM AT> FLASH

	/****************************/
    /*    UNINITIALIZED DATA    */
    /****************************/
	.bss :
	{
		_sbss = .;
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	}> SRAM
	
	.result :
	{
		*(.result)
	}> RESULT

	/********************************/
    /*   USER_HEAP_STACK SECTION	*/
    /********************************/
    /* User_heap_stack section, used to check that there is enough RAM left */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    }> SRAM
}

/* Highest address of the user mode stack */
/* Remember: the stack points downwards */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);	/* End of RAM */
/* END OF LINKERSCRIPT */