#include "gpio.h"
#include "stm32f446xx.h"

void gpio_init(void){

  //PC13 is input (00) User Button
  GPIOC->MODER &= ~(3U << (13 * 2));

  //PA5 is output (01) LED 
  GPIOA->MODER &= ~(3U << (5 * 2));
  GPIOA->MODER |= (1U << (5 * 2));


  //PA2 (TX) and PA3 (RX) are Alternate Functions (10) 
  //AF7 is the AF for USART2 Rx/TX for PA2 and PA3
  GPIOA->MODER &= ~(3U << (2 * 2));
  GPIOA->MODER &= ~(3U << (3 * 2));
  GPIOA->MODER |= (2U << (2 * 2));
  GPIOA->MODER |= (2U << (3 * 2));

  GPIOA->AFR[0] &= ~(0xF << (2 * 4));
  GPIOA->AFR[0] &= ~(0xF << (3 * 4));
  GPIOA->AFR[0] |= (0x7U << (2 * 4));
  GPIOA->AFR[0] |= (0x7U << (3 * 4));




}
