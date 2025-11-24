#include <stdint.h>
#include "systick.h"
#include "stm32f446xx.h"

extern uint32_t timer_ms = 0;

void SysTick_Handler(void){
  timer_ms++;
}

void SysTick_init(void){

  SysTick->LOAD = (SystemCoreClock / 1000) - 1; 
  SysTick->VAL = 0;
  SysTick->CTRL |= (1U << 0); //Enable Counter
  SysTick->CTRL |= (1U << 1); //Enable SysTick Interrupt 
  SysTick->CTRL |= (1U << 2); //Select Processor Clock Source

}
