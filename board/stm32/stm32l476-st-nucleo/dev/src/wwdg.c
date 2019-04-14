#include <stm32l476/wwdg.h>
#include <stm32l476/rcc.h>
#include <stm32l476/nvic.h>
#include <dev/led.h> 

void wwdg_init(void)
{
	/* enable watchdog */
	RCC->APB1ENR1 |= RCC_APB1ENR1_WWDGEN;
	/* configure for max interval */
	WWDG->CR = WWDG_CR_WDGA | WWDG_CR_T;
	/* set up prescaler and interrupt */
	WWDG->CFR = WWDG_CFR_EWI | WWDG_CFR_WDGTB | WWDG_CFR_W;
	/* set priority */
	NVIC_SETINTPRI(STM32_INT_WWDG, 0x00);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_WWDG);

}

/* kick the dog! */
void wwdg_kick(void)
{
	/* reset counter */
	WWDG->CR = WWDG_CR_T;
}

int wwdg_is_reset(void)
{
	return ((RCC->CSR) & (0x01<<30))?1:0;
}

/* watchdog interrupt routine */
void Watchdog_WWDGIsr(void)
{
	/* clean pending bit */
	WWDG->SR = 0x00;
	led_toggle();
	wwdg_kick();
}