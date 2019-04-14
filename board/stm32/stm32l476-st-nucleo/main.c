/*
 * main.c
 *
 *      Author: Andey
 */
#include <dev/led.h>
#include <dev/button.h>
#include <dev/wwdg.h>
#include <dev/pwm.h>

/* system entry point */
int main(void)
{
	//led_init();
	button_init();
	pwm_init();
	register_user_button_func(update_pwm_value);
	//wwdg_init();
	while(1);
	return 0;
}
