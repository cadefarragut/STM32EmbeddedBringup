#include "systick.h"

volatile uint32_t timer_ms = 0;

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

uint32_t get_time(void){
  return timer_ms;
}

void delay(uint32_t count){
  uint32_t start_time = timer_ms;
  while((timer_ms - start_time) < count){}
}
