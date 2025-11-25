#include "stm32f446xx.h"
#include "system_clock.h"
#include "systick.h"
#include "gpio.h"
#include "uart.h"

int main(void)
{
	system_clock_init();

  SysTick_init();

  gpio_init();

  uart_init();

    uart_write_str("Hello UART");
  uart_write_str("My name is Cade");

	while (1) {

    uint32_t button_pressed = ( GPIOC->IDR & (1U << 13) );

    if(button_pressed){
      delay(500);
      GPIOA->ODR &= ~(1U << 5 ); 
    } else {
      GPIOA->ODR |= (1U << 5 );
    }
	}
}
