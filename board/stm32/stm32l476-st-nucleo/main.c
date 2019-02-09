/*
 * main.c
 *
 *      Author: Andey
 */
#include <dev/led.h>
#include <dev/button.h>
/* system entry point */
int main(void)
{
	led_init();
	button_init();
	while(1);
	return 0;
}
