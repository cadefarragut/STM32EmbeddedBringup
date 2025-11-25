#include "stm32f446xx.h"
#include "system_clock.h"
#include "systick.h"
#include "gpio.h"
#include "uart.h"

extern volatile uint32_t timer_ms;

int main(void)
{
	system_clock_init();

  SysTick_init();

  gpio_init();

  uart_init();

  uint32_t start_time = 0;

	while (1) {
  
    if(timer_ms - start_time > 500){
      uart_write_str("Now: ");
      uart_write_num(timer_ms);
      uart_write_str(" Delta: ");
      uart_write_num(timer_ms-start_time);
      uart_write_char('\n');
      uart_write_char('\r');
      start_time = timer_ms;
      //uart_write_num(timer_ms);
      //`uart_write_char('\n');
      //art_write_char('\r');
    } 

    uint32_t button_pressed = ( GPIOC->IDR & (1U << 13) );

    if(button_pressed){
      delay(500);
      GPIOA->ODR &= ~(1U << 5 ); 
    } else {
      GPIOA->ODR |= (1U << 5 );
    }
	}
}
