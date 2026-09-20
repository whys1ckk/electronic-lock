#include <Arduino.h>
#include <avr/io.h>

#include "gpio.h"

void gpio_init()
{
    DDRD |= (1 << DDD4);       // D4 → OUTPUT
    DDRD &= ~(1 << DDD2);      // D2 → INPUT
    PORTD |= (1 << PORTD2);    // pull-up
}