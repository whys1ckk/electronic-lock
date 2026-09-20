#include <Arduino.h>
#include <avr/io.h>
#include "gpio.h"

int mode = 0;
int lastButtonState = 1;

void setup()
{   
    gpio_init();
}

void loop()
{
    int buttonState = PIND & (1 << PIND2);

    if (lastButtonState && !buttonState)
    {
        mode++;
    }

    if (mode > 3)
    {
        mode = 1;
    }

    gpio_set_led(mode);

    lastButtonState = buttonState;
}