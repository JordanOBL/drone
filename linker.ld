MEMORY {
  FLASH(rx): ORIGIN = 0x08000000, LENGTH = 64K
  RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS {
  .text : {
    . = ALIGN(4);
    *(.isr_vector) /* interrupt vector table */
    *(.text*) /* all code */
    *(.rodata*) /* read only dta */
  } > FLASH /*place all into flash*/

  .data : {
    _data_start = .;  /* symbol: RAM start of .data */
    *(.data*)  /* initialized variables */
    _data_end = .; /* symbol: RAM end of .data */
  } > RAM AT > FLASH  /* load from FLASH to RAM */

  _data_load_start = LOADADDR(.data);/* symbol: Flash source address */

  .bss : {
    _bss_start = .; /* symbol: start of uninitialized section */
    *(.bss*)          /* uninitialized variables */
    *(COMMON)         /* common symbols */
    _bss_end = .; /* symbol: end of bss */
  } > RAM             /* placed in RAM */

}


 _stack_top = ORIGIN(RAM) + LENGTH(RAM);
  PROVIDE(__stack_top = _stack_top);
