/* Entry Point */
ENTRY(Reset_Handler) /* The function named 'Reset_Handler' is defined */
                     /* in the 'startup.s' assembly file.             */

/* Generate a link error if heap and stack don't fit into RAM */
__heap_size = 0x200;  /* Required amount of heap  */
__stack_size = 0x400; /* Required amount of stack */

/* --------------------------------------------------------------------*/
/*                    MEMORY AREAS                                     */
/* --------------------------------------------------------------------*/
MEMORY
{
	ROM    (rx): ORIGIN = 0x08000000, LENGTH = 262144  /* 0x0804.0000 256 KBytes */
	DEBUG (rwx): ORIGIN = 0x20000F04, LENGTH = 4       /* 0x2000.0000 4 Bytes    */
	RESULT(rwx): ORIGIN = 0x20000F08, LENGTH = 4       /* 0x2000.0004 4 Bytes    */
	RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 3840    /* 0x2000.0F00 */
	RAM_  (rwx): ORIGIN = 0x20000F0C, LENGTH = 61688   /* 0x2001.0000 */
}

REGION_ALIAS("REGION_TEXT", RAM);
REGION_ALIAS("REGION_RODATA", RAM);
REGION_ALIAS("REGION_DATA", RAM);
REGION_ALIAS("REGION_BSS", RAM);
REGION_ALIAS("REGION_STACK_HEAP", RAM_);
REGION_ALIAS("REGION_RESULT", RESULT);
REGION_ALIAS("REGION_DEBUG", DEBUG);

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
	}> REGION_TEXT
	
	/*****************/
    /*    RO DATA    */
    /*****************/
	.rodata :
	{
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
	}> REGION_RODATA
	
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
	}> REGION_DATA
	
	data_size = SIZEOF(.data);

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
	}> REGION_BSS
	
	.result :
	{
		*(.result)
	}> REGION_RESULT
	
	.debug (NOLOAD):
	{
		*(.debug)
	}> REGION_DEBUG

	/********************************/
    /*   USER_HEAP SECTION	*/
    /********************************/
    . = ALIGN(4);
    __sheap = .;
}

/* Highest address of the user mode stack */
/* Remember: the stack points downwards */
_estack = ORIGIN(RAM) + LENGTH(RAM) + LENGTH(DEBUG) + LENGTH(RESULT) + LENGTH(RAM_);	/* End of RAM */
/* END OF LINKERSCRIPT */

/*

  /* User_heap_stack section, used to check that there is enough RAM left */
  .heap :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    _sheap = .;
    . = . + __heap_size;
    . = ALIGN(4);
    _eheap = .;
  }> RAM

*/