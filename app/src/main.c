#include <stdint.h>

#define PERIPH_BASE       0x40000000UL
#define AHB1PERIPH_BASE   (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE   (PERIPH_BASE + 0x00000000UL)

#define RCC_BASE          (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE        (AHB1PERIPH_BASE + 0x0000UL)
#define USART2_BASE       (APB1PERIPH_BASE + 0x4400UL)

/* RCC */
#define RCC_AHB1ENR       (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR       (*(volatile uint32_t *)(RCC_BASE + 0x40))

/* GPIOA */
#define GPIOA_MODER       (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL        (*(volatile uint32_t *)(GPIOA_BASE + 0x20))
#define GPIOA_ODR         (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

/* USART2 */
#define USART2_SR         (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR         (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR        (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1        (*(volatile uint32_t *)(USART2_BASE + 0x0C))

static void delay(volatile uint32_t count)
{
    while (count--) __asm__("nop");
}

void uart2_init(void)
{
    /* Enable GPIOA + USART2 clocks */
    RCC_AHB1ENR |= (1U << 0);  /* GPIOAEN */
    RCC_APB1ENR |= (1U << 17); /* USART2EN */

    /* PA2 = AF7 (USART2_TX) */
    /* MODER: set PA2 to AF (10b) */
    GPIOA_MODER &= ~(3U << (2 * 2));
    GPIOA_MODER |=  (2U << (2 * 2));

    /* AFRL: PA2 -> AF7 */
    GPIOA_AFRL &= ~(0xFU << (4 * 2));
    GPIOA_AFRL |=  (7U  << (4 * 2));

    /* Assuming 16 MHz clock, 115200 baud
     * BRR ≈ 16MHz / 115200 ≈ 138.9 -> 0x08B (approx)
     */
    USART2_BRR = 0x08B;

    /* Enable USART, TX */
    USART2_CR1 |= (1U << 13) | (1U << 3);
}

void uart2_write_char(char c)
{
    while (!(USART2_SR & (1U << 7))) {
        /* wait for TXE */
    }
    USART2_DR = (uint32_t)c;
}

void uart2_write_str(const char *s)
{
    while (*s) {
        uart2_write_char(*s++);
    }
}

int main(void)
{
    /* Enable GPIOA clock */
    RCC_AHB1ENR |= (1U << 0);

    /* PA5 as output (LED) */
    GPIOA_MODER &= ~(3U << (5 * 2));
    GPIOA_MODER |=  (1U << (5 * 2));

    uart2_init();
    uart2_write_str("Hello from STM32!\r\n");

    while (1) {
        /* Toggle LED */
        GPIOA_ODR ^= (1U << 5);
        uart2_write_str("Blink\r\n");
        delay(800000);
    }
}
