#include <stdint.h>
//You need to tell your C file that some symbol addresses (section start/end) will be provided by the linker:
// Vector table pointer (top of stack)
extern uint32_t* _stack_top;  // alias for __stack_top
// or: extern unsigned long __stack_top;

// Initialized data section in FLASH → copied to RAM
extern uint32_t* _data_load_start; // from FLASH (LOADADDR(.data))
extern uint32_t* _data_start;      // RAM start of .data
extern uint32_t* _data_end;        // RAM end of .data

// Uninitialized .bss section (zero-initialized)
extern uint32_t* _bss_start;
extern uint32_t* _bss_end;


extern int main(void);

//Its job is to get memory ready for your program
void Reset_Handler(void);

__attribute__ ((section(".isr_vector")))
               void(* const vector_table[])(void) = {
  (void (*)(void)) &_stack_top, //initial stack pointer
  Reset_Handler //reset_handler,
  //(add more tot the reset handler later)
};

void Reset_Handler(void) {
    // Copy .data section from FLASH to RAM
    uint32_t* src = _data_load_start;
    uint32_t* dst = _data_start;
    while (dst < _data_end) {
        *dst++ = *src++;
    }

    // Zero initialize the .bss section in RAM
    dst = _bss_start;
    while (dst < _bss_end) {
        *dst++ = 0;
    }

    // Call the main application
    main();
}

