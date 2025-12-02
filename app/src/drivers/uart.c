#include "uart.h"
#include "ring_buffer.h"

#define USART2_RX_BUF_SIZE 64

static volatile uint8_t usart2_rx_buf[USART2_RX_BUF_SIZE];
static ring_buffer_t usart2_rx_rb;


void uart_init(void){
  /* USARTDIV = f_PCLK / (16 x BAUDRATE) => 16MHz / (16 x 9600) = 104.16666
  *  104 == 0x68, 0.1666(16) == 2.666 -> 2 == 0x2
  *  BRR = (mantissa << 4) | (fraction & 0xF) => (0x16 << 4) | (0x13)
  *  BRR == 0x682
  */
  USART2->BRR = 0x0682;
  USART2->CR1 = 0; //Clear Everything
  USART2->CR1 &= ~(1U << 12); //Set M == 8 data bits
  USART2->CR1 &= ~(1U << 10); //PCE=0 == no parity
  USART2->CR1 |= (1U << 3);  // Enable TX
  USART2->CR1 |= (1U << 2);  // Enable RX
  USART2->CR1 |= (1U << 5);  // Enable RXNEIE Interrupt
  USART2->CR1 |= (1U << 13); // Enable USART
  
  rb_init(&usart2_rx_rb, usart2_rx_buf, USART2_RX_BUF_SIZE);
  
  NVIC_EnableIRQ(USART2_IRQn);
}

void uart_write_char(char c){
  while(!(USART2->SR & (1U << 7))){}
    USART2->DR = (uint8_t)c;
}

void uart_write_str(char *s){
  while(*s != '\0'){
    uart_write_char(*s);
    s++;
  }
}

void uart_write_num(uint32_t n){
  char buf[12];
  int i = 0;

  if(n == 0) {
    uart_write_char('0');
    return;
  }

  while(n > 0){
    buf[i++] = '0' + (n % 10);
    n = n / 10;
  }

  while(i--){
    uart_write_char(buf[i]);
  }
}

int usart2_getchar_nonblocking(uint8_t *out){
    return rb_pop(&usart2_rx_rb, out);
}

void USART2_IRQHandler(void){

  uint32_t sr = USART2->SR;;

  if (sr & (1U << 5)){

    uint8_t data = (uint8_t)USART2->DR;
    rb_push_isr(&usart2_rx_rb, data);

  }
}
