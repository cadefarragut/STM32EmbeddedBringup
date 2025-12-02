#include "system_clock.h"

void system_clock_init(void)
{
  //Enable Clock for GPIOC
  RCC->AHB1ENR |= (1U << 2);

  //Enable Clock for GPIOA
  RCC->AHB1ENR |= (1U << 0);

  //Enable Clock for USART2
  RCC->APB1ENR |= (1U << 17);

  //Enable Clock for SYSCFGEN
  RCC->APB2ENR |= (1U << 14); 


	// SystemInit() is already defined in system_stm32f4xx.c
	// Will update any clock changes if needed

	SystemCoreClockUpdate();
}

