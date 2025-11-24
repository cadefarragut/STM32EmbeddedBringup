#include "stm32f446xx.h"
#include "system_clock.h"
#include "gpio.h"

int main(void)
{
	system_clock_init();

  gpio_init();

	while (1) {
    	
	}
}
