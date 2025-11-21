#include "stm32f446xx.h"
#include "system_stm32f4xx.h"
#include "system_clock.h"

void system_clock_init(void)
{
	// SystemInit() is already defined in system_stm32f4xx.c
	// Will update any clock changes if needed

	SystemCoreClockUpdate();
}

