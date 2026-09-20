#include <Arduino.h>
#include <avr/io.h>
#include "gpio.h"

void gpio_init()
{   
    DDRD |= (1 << DDD3);       // D3 → OUTPUT
    DDRD |= (1 << DDD4);       // D4 → OUTPUT
    DDRD |= (1 << DDD5);       // D5 → OUTPUT
    DDRD &= ~(1 << DDD2);      // D2 → INPUT
    PORTD |= (1 << PORTD2);  
    PORTD &= ~(1 << PORTD3);
    PORTD &= ~(1 << PORTD4);
    PORTD &= ~(1 << PORTD5);  
    
}

void gpio_set_led(int mode)
{
    if (mode == 1)
    {
        PORTD |= (1 << PORTD3);
        PORTD &= ~(1 << PORTD4);
        PORTD &= ~(1 << PORTD5);
    }
    else if (mode == 2)
    {
        PORTD &= ~(1 << PORTD3);
        PORTD |= (1 << PORTD4);
        PORTD &= ~(1 << PORTD5);
    }
    else if (mode == 3)
    {
        PORTD &= ~(1 << PORTD3);
        PORTD &= ~(1 << PORTD4);
        PORTD |= (1 << PORTD5);
    }
    
}