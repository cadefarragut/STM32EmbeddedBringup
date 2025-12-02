#include "stm32f446xx.h"
#include "system_clock.h"
#include "systick.h"
#include "gpio.h"
#include "uart.h"
#include "button_exti.h"

extern volatile uint32_t timer_ms;

int main(void)
{
	system_clock_init();

  SysTick_init();

  gpio_init();

  uart_init();

  button_exti_init();

  uint32_t start_time = 0;

	while (1) {

    uint32_t button_pressed = ( GPIOC->IDR & (1U << 13) );

    uint8_t c;
    if(usart2_getchar_nonblocking(&c) == 0){
      uart_write_char((char)c);
    }
	}
}
