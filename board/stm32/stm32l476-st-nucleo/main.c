/*
 * main.c
 *
 *      Author: Andey
 */
#include <dev/led.h>
#include <dev/button.h>
#include <dev/wwdg.h>

/* system entry point */
int main(void)
{
	led_init();
	button_init();
	wwdg_init();
	while(1);
	return 0;
}
