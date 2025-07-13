#include <stdint.h>
#define RCC_APB2ENR (*(volatile uint32_t*)0x40021018)
#define GPIOC_CRH (*(volatile uint32_t*)0x40011004)
// #define GPIOC_ODR (*(volatile uint32_t*)0x4001100C //general purpose i/o output data register using bssr instead for atomicity
#define GPIOC_BSRR (*(volatile uint32_t*)0x40011010) //BIT SET RESET
#define GPIOA_CRH (*(volatile uint32_t*)0x40010804) //pin 9 = bits 4-7, pin 10 = bits 8-11
#define USART1_SR (*(volatile uint32_t*)0x40013800) //Address offset: 0x00 Reset value: 0x00C0
#define USART1_DR (*(volatile uint32_t*)0x40013804) //Address offset: 0x04 Reset value: undefined | DR[8:0]: Data value
#define USART1_BRR (*(volatile uint32_t*)0x40013808) //Address offset: 0x08 Reset value: 0x0000
#define USART1_CR1 (*(volatile uint32_t*)0x4001380C) //Address offset: 0x0C Reset value: 0x0000
#define USART1_CR2 (*(volatile uint32_t*)0x40013810) //Address offset: 0x10 Reset value: 0x0000
/*MEMORY MAP
 0x4002 1000 - 0x4002 13FF Reset and clock control RCC/
 0x4001 3800 - 0x4001 3BFF USART1 
 0x4001 0800 - 0x4001 0BFF GPIO Port A
 0x4001 1000 - 0x4001 13FF GPIO Port C
 0x4001 0000 - 0x4001 03FF AFIO

 USART1_TX PA9 
 USART1_RX PA10
 */
// Function declarations
void turn_off(void);
void turn_on(void);
void blink_loop(void);
void delay(volatile uint32_t count);
//Its job is to get memory ready for your program

int main(void){
  //turn on the reset clock control for APB2 (alternate port bus commuicating to set of periphials holding PORT C )
  RCC_APB2ENR |= (1 << 4); // Set bit 4 (IOPCEN) bitwise OR (pg113 rm0008)
  RCC_APB2ENR |= (1 << 14); // enables the clock to the USART1 peripheral.
  GPIOC_CRH &= ~(0xF << 20);  // Clear pc13 bits 23–20 (rm page 172)
  GPIOC_CRH |= (0x2 << 20);  // Set pc13 bits to 0b0010 (output push-pull, 2 MHz) (rm page 172)
  GPIOA_CRH &= ~(0xF << 4); //Clear bits 4 - 7 for pin_9 OUTPUT TX
    GPIOA_CRH |= (0xA << 4); //set Bits 4 - 7 for pin_9 0b1010  CNF= 10: Alternate Function output Push-Pull (reset state);mode = output/speed 2MHz (10);
    // For alternate function inputs, the port must be configured in Input mode (floating, pullup or pull-down) and the input pin must be driven externally.↓
    GPIOA_CRH &= ~(0xF << 8); //Clear bits 8 - 11 for pin_10 INPUT RX
    GPIOA_CRH |= (0x4 << 8); //set Bits 8 -11 for pin_10 0b0100  CNF= 01: Floating input (reset state);mode = output/speed 2MHz (00);

    USART1_CR1 |= (1 << 13); //USART ENABLE
    USART1_CR1 &= ~(1 << 12); // USART WORD LENGTH = 8
    USART1_CR1 |= (1 << 3); //tx ENABLE
    USART1_CR1 |= (1 << 2); // rx ENABLE
    USART1_CR2 &= ~(0x3 << 12); //00: 1 Stop bit bits 12-13 

    //USARTDIV = Fck / BaudRate
    //BRR = mantissa + fraction
    //Fck = peripheral clock frequency
    //BaudRate = desired baud (e.g. 9600)
    //BRR = 16-bit register (USART_BRR), split into:
    ////Mantissa: high bits
    ////Fraction: low 4 bits
    USART1_BRR = 0x0271;   // 115 200 Bd when PCLK2 = 72 MHz
 // 0x1D4C; the correct 16-bit result for sim

  blink_loop();
}

void turn_off(void) {
  // Set PC13 HIGH (bit 13 in BSRR)
  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  USART1_DR = 'O';  // Transmit ASCII 'O'
  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  USART1_DR = 'F';  // Transmit ASCII 'F'
  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  USART1_DR = 'F';  // Transmit ASCII 'F'
  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  USART1_DR = '\n';  // Transmit ASCII '/n'

  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  GPIOC_BSRR = (1 << 13);
}

void turn_on(void) {
  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  USART1_DR = 'O';  // Transmit ASCII 'A'
  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  USART1_DR = 'N';  // Transmit ASCII 'F'
  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  USART1_DR = '\n';  // Transmit ASCII '/n'

  while (!(USART1_SR & (1 << 7)));  // Wait until TXE == 1
  // Set PC13 LOW (bit 13 in upper 16 bits of BSRR)
  GPIOC_BSRR = (1 << (13 + 16));  // i.e., bit 29
}

void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop");  // Prevent optimization
    }
}

void blink_loop(void){
  while(1){
    turn_off();
    delay(500000);
    turn_on();
    delay(500000);
  }
}

