# 0 "main.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "main.c"
# 1 "/opt/homebrew/Cellar/arm-none-eabi-gcc/15.1.0/lib/gcc/arm-none-eabi/15.1.0/include/stdint.h" 1 3 4
# 14 "/opt/homebrew/Cellar/arm-none-eabi-gcc/15.1.0/lib/gcc/arm-none-eabi/15.1.0/include/stdint.h" 3 4
# 1 "/opt/homebrew/Cellar/arm-none-eabi-gcc/15.1.0/lib/gcc/arm-none-eabi/15.1.0/include/stdint-gcc.h" 1 3 4
# 34 "/opt/homebrew/Cellar/arm-none-eabi-gcc/15.1.0/lib/gcc/arm-none-eabi/15.1.0/include/stdint-gcc.h" 3 4

# 34 "/opt/homebrew/Cellar/arm-none-eabi-gcc/15.1.0/lib/gcc/arm-none-eabi/15.1.0/include/stdint-gcc.h" 3 4
typedef signed char int8_t;


typedef short int int16_t;


typedef long int int32_t;


typedef long long int int64_t;


typedef unsigned char uint8_t;


typedef short unsigned int uint16_t;


typedef long unsigned int uint32_t;


typedef long long unsigned int uint64_t;




typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef long int int_least32_t;
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef short unsigned int uint_least16_t;
typedef long unsigned int uint_least32_t;
typedef long long unsigned int uint_least64_t;



typedef int int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef long long unsigned int uint_fast64_t;




typedef int intptr_t;


typedef unsigned int uintptr_t;




typedef long long int intmax_t;
typedef long long unsigned int uintmax_t;
# 15 "/opt/homebrew/Cellar/arm-none-eabi-gcc/15.1.0/lib/gcc/arm-none-eabi/15.1.0/include/stdint.h" 2 3 4
# 2 "main.c" 2



# 4 "main.c"
extern uint32_t* _stack_top;



extern uint32_t* _data_load_start;
extern uint32_t* _data_start;
extern uint32_t* _data_end;


extern uint32_t* _bss_start;
extern uint32_t* _bss_end;


extern int main(void);


void Reset_Handler(void);

__attribute__ ((section(".isr_vector")))
               void(* const vector_table[])(void) = {
  (void (*)(void)) &_stack_top,
  Reset_Handler

};

void Reset_Handler(void) {

    uint32_t* src = _data_load_start;
    uint32_t* dst = _data_start;
    while (dst < _data_end) {
        *dst++ = *src++;
    }


    dst = _bss_start;
    while (dst < _bss_end) {
        *dst++ = 0;
    }


    main();
}
