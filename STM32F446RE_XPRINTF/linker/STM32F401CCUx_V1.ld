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
	ROM    (rx): ORIGIN = 0x08000000, LENGTH = 262144  /* 0x0804.0000 256 KBytes */
	DEBUG (rwx): ORIGIN = 0x20000000, LENGTH = 4       /* 0x2000.0000 4 Bytes    */
	RESULT(rwx): ORIGIN = 0x20000004, LENGTH = 4       /* 0x2000.0004 4 Bytes    */
	RAM   (rwx): ORIGIN = 0x20000008, LENGTH = 65528   /* 0x2001.0000 */
}

REGION_ALIAS("REGION_TEXT", ROM);
REGION_ALIAS("REGION_RODATA", ROM);
REGION_ALIAS("REGION_DATA", RAM);
REGION_ALIAS("REGION_BSS", RAM);
REGION_ALIAS("REGION_STACK_HEAP", RAM);
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
	.text 0x08000000:		/* <=> .text 0x08000000: */
	{
		*(.isr_vector)
		*(.text)
	}> REGION_TEXT
	
	/*****************/
    /*    RO DATA    */
    /*****************/
	.rodata : 				/* <=> .rodata 0x08001000: */
	{
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
	}> REGION_RODATA
	
	_la_data = LOADADDR(.data);
  
	/****************************/
    /*    INITIALIZED DATA      */
    /****************************/
	.data : AT ( _etext )
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
    }> REGION_STACK_HEAP
}

/* Highest address of the user mode stack */
/* Remember: the stack points downwards */
_estack = ORIGIN(RAM) + LENGTH(RAM);	/* End of RAM */
/* END OF LINKERSCRIPT */