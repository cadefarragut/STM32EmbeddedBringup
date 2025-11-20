#include <stdint.h>
#include <stm32f446xx.h>

uint32_t SystemCoreClock = 16000000U;

void SystemInit(void)
{
    /* For now we just assume default reset clock config (HSI @ 16MHz). */
    /* Later you can set PLL, HCLK, PCLK, etc. */
}
