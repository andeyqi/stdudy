/*
 * main.c
 *
 *      Author: Andey
 */
#include <dev/led.h>
/* system entry point */
int main(void)
{
	led_test();
	while(1);
	return 0;
}
