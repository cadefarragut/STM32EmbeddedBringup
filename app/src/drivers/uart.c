#include "uart.h"
#include "stm32f446xx.h"


void uart_init(void){
  /* USARTDIV = f_PCLK / (16 x BAUDRATE) => 42MHz / (16 x 9600h) = 273.4375
  *  BRR = (mantissa << 4) | (fraction & 0xF) => (0x16 << 4) | (0x13)
  *  273 == 0x111, 0.7865(16) == 12.58 -> 13 == 0xD
  *  BRR == 0x16D
  */
  USART2->BRR = 0x0682;
  USART2->CR1 = 0; //Clear Everything
  USART2->CR1 &= ~(1U << 12); //Set M == 8 data bits
  USART2->CR1 |= (1U << 3);  // Enable TX
  USART2->CR1 |= (1U << 2);  // Enable RX
  USART2->CR1 |= (1U << 13); // Enable USART
}

void uart_write_char(char c){
  while(!(USART2->SR & (1U << 7))){}
    USART2->DR = (uint8_t)c;
}

void uart_write_str(char s[]){
  int i = 0;
  while(s[i] != '\0'){
    uart_write_char(s[i]);
    i++;
  }
  uart_write_char('\n');
  uart_write_char('\r');
}
