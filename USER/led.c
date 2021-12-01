#include "led.h"

void led_gpio_config() 
{
	// open GPIOC clock
	RCC->APB2ENR |= 1 << 4;
	
	// set GPIOC.2 type = push-pull output
	GPIOC->CRL &= 0xfffff0ff;
	GPIOC->CRL |= 0x00000300;
    // set GPIOC.2 level = level, it means turn on led
    GPIOC->ODR &= ~(1 << 2);
	
	// set GPIOC.3 type = push-pull output
	GPIOC->CRL &= 0xffff0fff;
	GPIOC->CRL |= 0x00003000;
	
	// set GPIOC.3 level = high, it means turn off led
	GPIOC->ODR |= 1 << 3;
}

