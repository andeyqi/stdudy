#include <stm32l476/rcc.h>
#include <stm32l476/gpio.h>

void led_init(void)
{
    /* enable GPIOA RCC clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    /* config GPIOA5 PP out mode */
    GPIOA->MODER &= ~(0x03 << (5*2));
    GPIOA->MODER |= GPIO_MODER_MODER5_0;    
    /* config Output push-pull */
    GPIOA->OTYPER &= ~(0x01 << 5);
    
    /* config GPIO port output speed */
    GPIOA->OSPEEDR &= ~(0x03 << (5*2));
    GPIOA->OSPEEDR |=  (0x03 << (5*2));

    /* config GPIO port pull-up/pull-down */
    GPIOA->PUPDR &= ~(0x03 << (5*2));
    GPIOA->PUPDR |=  (0x01 << (5*2));
}

void led_on(void)
{
    GPIOA->ODR |= (0x01 << 5);
}

void led_off(void)
{
    GPIOA->ODR &= ~(0x01 << 5);
}

void led_toggle(void)
{
    GPIOA->ODR ^= (0x01 << 5);
}

static void delay(unsigned int num)
{
    volatile int i = 1000;
    while(num--)
    {
        for(;i > 0; i--);
         i = 1000;
    }
}

void led_test(void)
{
    int i_loop;
    led_init();
    for(i_loop = 0;i_loop < 10 ;i_loop++)
    {
        led_toggle();
        delay(100);
    }
}
