#include <stm32l476/rcc.h>
#include <stm32l476/timer.h>
#include <stm32l476/gpio.h>

void pwm_init(void)
{
	/* PWM 输出引脚配置 */
	/* 1.开启GPIO时钟 */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	/* 2.配置GPIO引脚 */
	/* 2.1 设置GPIO引脚复用模式*/
	GPIOA->MODER &= ~GPIO_MODER_MODER5;
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	/* 2.2 配置下拉 */
	GPIOA->PUPDR &= GPIO_PUPDR_PUPDR5;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR5_1;
	/* 2.3 设置引脚复用为定时器模式 */
	GPIOA->AFRL &= ~GPIO_AFRL_AFRL5;
	GPIOA->AFRL |= GPIO_AFRL_AFRL5_AF1;
	/* 2.4 配置引脚输出速度 */
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
	GPIOA->OSPEEDR |= ~GPIO_OSPEEDER_OSPEEDR5_1;
	/* TIMER 配置 */
	/* 1.开启TIMER时钟 */
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	/* 2.配置定时器时间参数 */
	/* 2.1 设置定时器时基频率 */
	TIM2->PSC = (4000000/10000 -1);
	/* 2.2 使能自动加载 */
	TIM2->CR1 |= TIM_CR1_ARPE;
	/* 2.3 设置自动加载计数值 */
	TIM2->ARR = 10000/100 -1;
	/* 启动定时器 */
}