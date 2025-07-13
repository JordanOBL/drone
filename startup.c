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

// Function declarations
void Reset_Handler(void);
void Default_Handler(void);
void USART1_IRQHandler(void);


// Weak aliases for unused handlers
#define WEAK_DEFAULT(handler) \
    void handler(void) __attribute__ ((weak, alias("Default_Handler")))

// Cortex-M system exceptions
WEAK_DEFAULT(NMI_Handler);
WEAK_DEFAULT(HardFault_Handler);
WEAK_DEFAULT(MemManage_Handler);
WEAK_DEFAULT(BusFault_Handler);
WEAK_DEFAULT(UsageFault_Handler);
WEAK_DEFAULT(SVC_Handler);
WEAK_DEFAULT(DebugMon_Handler);
WEAK_DEFAULT(PendSV_Handler);
WEAK_DEFAULT(SysTick_Handler);

// STM32F103 IRQ handlers (first 43)
WEAK_DEFAULT(WWDG_IRQHandler);
WEAK_DEFAULT(PVD_IRQHandler);
WEAK_DEFAULT(TAMPER_IRQHandler);
WEAK_DEFAULT(RTC_IRQHandler);
WEAK_DEFAULT(FLASH_IRQHandler);
WEAK_DEFAULT(RCC_IRQHandler);
WEAK_DEFAULT(EXTI0_IRQHandler);
WEAK_DEFAULT(EXTI1_IRQHandler);
WEAK_DEFAULT(EXTI2_IRQHandler);
WEAK_DEFAULT(EXTI3_IRQHandler);
WEAK_DEFAULT(EXTI4_IRQHandler);
WEAK_DEFAULT(DMA1_Channel1_IRQHandler);
WEAK_DEFAULT(DMA1_Channel2_IRQHandler);
WEAK_DEFAULT(DMA1_Channel3_IRQHandler);
WEAK_DEFAULT(DMA1_Channel4_IRQHandler);
WEAK_DEFAULT(DMA1_Channel5_IRQHandler);
WEAK_DEFAULT(DMA1_Channel6_IRQHandler);
WEAK_DEFAULT(DMA1_Channel7_IRQHandler);
WEAK_DEFAULT(ADC1_2_IRQHandler);
WEAK_DEFAULT(USB_HP_CAN_TX_IRQHandler);
WEAK_DEFAULT(USB_LP_CAN_RX0_IRQHandler);
WEAK_DEFAULT(CAN_RX1_IRQHandler);
WEAK_DEFAULT(CAN_SCE_IRQHandler);
WEAK_DEFAULT(EXTI9_5_IRQHandler);
WEAK_DEFAULT(TIM1_BRK_IRQHandler);
WEAK_DEFAULT(TIM1_UP_IRQHandler);
WEAK_DEFAULT(TIM1_TRG_COM_IRQHandler);
WEAK_DEFAULT(TIM1_CC_IRQHandler);
WEAK_DEFAULT(TIM2_IRQHandler);
WEAK_DEFAULT(TIM3_IRQHandler);
WEAK_DEFAULT(TIM4_IRQHandler);
WEAK_DEFAULT(I2C1_EV_IRQHandler);
WEAK_DEFAULT(I2C1_ER_IRQHandler);
WEAK_DEFAULT(I2C2_EV_IRQHandler);
WEAK_DEFAULT(I2C2_ER_IRQHandler);
WEAK_DEFAULT(SPI1_IRQHandler);
WEAK_DEFAULT(SPI2_IRQHandler);
WEAK_DEFAULT(USART1_IRQHandler);  // You will define this
WEAK_DEFAULT(USART2_IRQHandler);
WEAK_DEFAULT(USART3_IRQHandler);
WEAK_DEFAULT(EXTI15_10_IRQHandler);
WEAK_DEFAULT(RTCAlarm_IRQHandler);
WEAK_DEFAULT(USBWakeUp_IRQHandler);

// Vector table (60 entries)
__attribute__ ((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))(&_stack_top),   // Initial stack pointer
    Reset_Handler,                   // Reset
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,                      // Reserved
    SVC_Handler,
    DebugMon_Handler,
    0,                               // Reserved
    PendSV_Handler,
    SysTick_Handler,

    // External Interrupts (IRQs 0–42)
    WWDG_IRQHandler,                 // 0
    PVD_IRQHandler,                 // 1
    TAMPER_IRQHandler,              // 2
    RTC_IRQHandler,                 // 3
    FLASH_IRQHandler,               // 4
    RCC_IRQHandler,                 // 5
    EXTI0_IRQHandler,               // 6
    EXTI1_IRQHandler,               // 7
    EXTI2_IRQHandler,               // 8
    EXTI3_IRQHandler,               // 9
    EXTI4_IRQHandler,               // 10
    DMA1_Channel1_IRQHandler,       // 11
    DMA1_Channel2_IRQHandler,       // 12
    DMA1_Channel3_IRQHandler,       // 13
    DMA1_Channel4_IRQHandler,       // 14
    DMA1_Channel5_IRQHandler,       // 15
    DMA1_Channel6_IRQHandler,       // 16
    DMA1_Channel7_IRQHandler,       // 17
    ADC1_2_IRQHandler,              // 18
    USB_HP_CAN_TX_IRQHandler,       // 19
    USB_LP_CAN_RX0_IRQHandler,      // 20
    CAN_RX1_IRQHandler,             // 21
    CAN_SCE_IRQHandler,             // 22
    EXTI9_5_IRQHandler,             // 23
    TIM1_BRK_IRQHandler,            // 24
    TIM1_UP_IRQHandler,             // 25
    TIM1_TRG_COM_IRQHandler,        // 26
    TIM1_CC_IRQHandler,             // 27
    TIM2_IRQHandler,                // 28
    TIM3_IRQHandler,                // 29
    TIM4_IRQHandler,                // 30
    I2C1_EV_IRQHandler,             // 31
    I2C1_ER_IRQHandler,             // 32
    I2C2_EV_IRQHandler,             // 33
    I2C2_ER_IRQHandler,             // 34
    SPI1_IRQHandler,                // 35
    SPI2_IRQHandler,                // 36
    USART1_IRQHandler,              // 37 <-- you're using this one
    USART2_IRQHandler,              // 38
    USART3_IRQHandler,              // 39
    EXTI15_10_IRQHandler,           // 40
    RTCAlarm_IRQHandler,            // 41
    USBWakeUp_IRQHandler            // 42
};

// Default handler
void Default_Handler(void) {
    while (1);  // Hang for debugging
}

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


