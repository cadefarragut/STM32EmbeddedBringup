#include "stm32f4xx.h"
#include "button_exti.h"

void button_exti_init(void)
{
    SYSCFG->EXTICR[3] &= ~(0xF << 4);  // Clear bits for EXTI13
    SYSCFG->EXTICR[3] |=  (0x2 << 4);  // 0x2 = GPIOC for EXTI13

    // Configure EXTI line 13
    EXTI->IMR  |=  (1U << 13);    // Unmask interrupt
    EXTI->RTSR |=  (1U << 13);    // Trigger on rising edge
    EXTI->FTSR &= ~(1U << 13);    // No falling-edge trigger

    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1U << 13)) {
        EXTI->PR = (1U << 13);
        // toggle LED PA5
        GPIOA->ODR ^= (1U << 5);
    }
}

