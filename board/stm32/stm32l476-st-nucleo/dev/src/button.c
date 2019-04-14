#include <stm32l476/rcc.h>
#include <stm32l476/gpio.h>
#include <stm32l476/syscfg.h>
#include <stm32l476/exti.h>
#include <stm32l476/nvic.h>
#include <dev/led.h> 
#include <dev/button.h> 
#include <stdlib.h>

static button_callback g_func = NULL;

void button_init(void)
{
	//ExtiMux_Init();
	/* enable gpioc */
	RCC->AHB2ENR |= (0X01 << 2);
	/* enable syscfg */
	RCC->APB2ENR |= 0X01;
	/* config gpio inputmode */
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	/* config interrupt mode */
	SYSCFG->EXTICR4 &= ~(0x0f << 4);
	SYSCFG->EXTICR4 |= (0x02 << 4);
	/* configure for falling edge detection */
	EXTI->RTSR1 |= (0x01 << 13);
	EXTI->FTSR1 |= (0x01 << 13);
	/* enable interrupts */
	EXTI->IMR1 |= 0x01 << 13;
	/* set priority */
	NVIC_SETINTPRI(STM32_INT_EXTI10_15, 0xf0);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_EXTI10_15);
}

/* sw1 interrupt */
void Buttons_Exti13Isr(void)
{
	/* clean pending bit */
	EXTI->PR1 = 0x01 << 13;
	/* button down is falling trigger up is rising trigger */
	if(GPIOC->IDR & (0x01 << 13))
	{
		if(g_func)
			g_func();
	}
}

void register_user_button_func(button_callback func)
{
	g_func = func;
}
