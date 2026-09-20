#include <Arduino.h>
#include <avr/io.h>

int mode = 0;
int lastButtonState = 1;

void setup()
{   
    DDRD |= (1 << DDD3);       // D3 → OUTPUT
    DDRD |= (1 << DDD4);       // D4 → OUTPUT
    DDRD |= (1 << DDD5);       // D5 → OUTPUT
    DDRD &= ~(1 << DDD2);      // D2 → INPUT
    PORTD |= (1 << PORTD2);    
    
}

void loop()
{   
    int buttonState = PIND & (1 << PIND2); 

    if (lastButtonState && !buttonState)
    {
        mode++;
    }
    if (mode > 2)
    {
        mode = 0;
    }
    if (mode == 0)
    {
        PORTD |= (1 << PORTD3); // D3 → HIGH
        PORTD &= ~(1 << PORTD4); // D4 → LOW
        PORTD &= ~(1 << PORTD5); // D5 → LOW
    }
    else if (mode == 1)
    {
        PORTD &= ~(1 << PORTD3);  // D3 → LOW
        PORTD |= (1 << PORTD4); // D4 → HIGH
        PORTD &= ~(1 << PORTD5); // D5 → LOW
    }
    else if (mode == 2)
    {
        PORTD &= ~(1 << PORTD3); // D3 → LOW
        PORTD &= ~(1 << PORTD4);  // D4 → LOW
        PORTD |= (1 << PORTD5); // D5 → HIGH
    }

    lastButtonState = buttonState;
}