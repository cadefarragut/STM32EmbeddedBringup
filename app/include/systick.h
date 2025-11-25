#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include "stm32f446xx.h"
void SysTick_Handler(void);
void SysTick_init(void);
uint32_t get_time(void);
void delay(uint32_t);

#endif

