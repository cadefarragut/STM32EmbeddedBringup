#include "gpio.h"
#include "stm32f446xx.h"

void gpio_init(void){

  //PC13 is input (00) User Button
  GPIOC->MODER &= ~(3U << (13 * 2));

  //PA5 is output (01) LED 
  GPIOA->MODER &= ~(3U << (5 * 2));
  GPIOA->MODER |= (1U << (5 * 2));


}
