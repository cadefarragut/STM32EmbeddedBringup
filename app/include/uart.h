
#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "stm32f446xx.h"

void uart_init(void);
void uart_write_char(char c);
void uart_write_str(char *s);
void uart_write_num(uint32_t n);
int usart2_getchar_nonblocking(uint8_t *out);
void USART2_IRQHandler(void);

#endif
