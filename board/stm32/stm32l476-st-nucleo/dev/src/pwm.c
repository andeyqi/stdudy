#include <stm32l476/rcc.h>
#include <stm32l476/timer.h>
#include <stm32l476/gpio.h>
#include <dev/button.h>

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
	/* 2.4 设定PWM工作模式1 */
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	/* 2.5 设置PWM模式占空比 */
	TIM2->CCR1 = 0;
	/* 2.6 Output Compare 1 preload enable */
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
	/* 2.7 Enable output channel 1 */
	TIM2->CCER |= TIM_CCER_CC1E;
	/* 2.8 Enable counter */
	TIM2->CR1 |= TIM_CR1_CEN;
	/* 2.9 Force update generation */
	TIM2->EGR |= TIM_EGR_UG;
	/* 启动定时器 */
}

static void pwm_set_value(int value)
{
	TIM2->CCR1 = (TIM2->ARR+1)*value/100;
}

void update_pwm_value(void)
{
	static int value = 0;
	pwm_set_value(value);
	value += 10;
	if(value == 110)
		value = 0;
}