#include <Arduino.h>
#include <avr/io.h>
#include "gpio.h"

void gpio_init()
{
    DDRD |= (1 << DDD3); 
    DDRD |= (1 << DDD4); 
    DDRD |= (1 << DDD5);

    DDRD &= ~(1 << DDD2);   
    PORTD |= (1 << PORTD2); 

    DDRD &= ~(1 << DDD6);   
    PORTD |= (1 << PORTD6); 

    PORTD &= ~(1 << PORTD3);
    PORTD &= ~(1 << PORTD4);
    PORTD &= ~(1 << PORTD5);
}

void gpio_set_led(int mode)
{
    PORTD &= ~(1 << PORTD3);
    PORTD &= ~(1 << PORTD4);
    PORTD &= ~(1 << PORTD5);

    if (mode == 0)
    {
        PORTD |= (1 << PORTD3);
    }
    else if (mode == 1)
    {
        PORTD |= (1 << PORTD5);
    }
    else if (mode == 2)
    {
        PORTD |= (1 << PORTD4);
    }
    else if (mode == 3)
    {
        PORTD |= (1 << PORTD3);
    }
}