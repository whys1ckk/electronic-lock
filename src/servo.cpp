#include <Arduino.h>
#include <avr/io.h>
#include "servo.h"

void servo_init()
{
    DDRB |= (1 << DDB1);

    ICR1 = 39999;

    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << WGM11);

    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << WGM13);

    TCCR1B |= (1 << CS11);

    servo_close();
}

void servo_open()
{
    OCR1A = 2000;
}

void servo_close()
{
    OCR1A = 4000;
}