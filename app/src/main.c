#include "stm32f446xx.h"
#include "system_clock.h"
#include "systick.h"
#include "gpio.h"

int main(void)
{
	system_clock_init();

  SysTick_init();

  gpio_init();

	while (1) {

    uint32_t button_pressed = ( GPIOC->IDR & (1U << 13) );

    if(button_pressed){
      GPIOA->ODR &= ~(1U << 5 );
    } else {
      GPIOA->ODR |= (1U << 5 );
    }
	}
}
