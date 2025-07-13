ENTRY(Reset_Handler)

MEMORY {
  FLASH(rx): ORIGIN = 0x08000000, LENGTH = 64K
  RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS {  /* Place vector table and .text in FLASH */
    .isr_vector : {
    KEEP(*(.isr_vector))
  } > FLASH
  .text : {
    *(.text*) /* all code */
    *(.rodata*) /* read only dta */
  } > FLASH /*place all into flash*/

 .data : AT(LOADADDR(.text) + SIZEOF(.text)) {
    _data_load_start = LOADADDR(.data);
    _data_start = .;
    *(.data*)
    _data_end = .;
  } > RAM


  .bss : {
    _bss_start = .; /* symbol: start of uninitialized section */
    *(.bss*)          /* uninitialized variables */
    *(COMMON)         /* common symbols */
    _bss_end = .; /* symbol: end of bss */
  } > RAM             /* placed in RAM */
    . = ALIGN(4);
  _stack_top = ORIGIN(RAM) + LENGTH(RAM);
  PROVIDE(__stack_top = _stack_top);
}



