#include <Arduino.h>
#include <avr/io.h>
#include "gpio.h"

int mode = 0;
int lastButtonState = 1;
int lastButtonState2 = 1;
int pin[4] = {1, 2, 3, 4};
int correctPin[4] = {1, 2, 3, 4};
int pinIndex = 0;
int currentDigit = 0;
bool correct = true;

void setup()
{   
    gpio_init();
    Serial.begin(9600);
}

void loop()
{
    int button1 = PIND & (1 << PIND2);
    int button2 = PIND & (1 << PIND6);

    if (lastButtonState && !button1)
    {   
        currentDigit++;
    }

    if (currentDigit > 9)
    {
        currentDigit = 0;
    }
    if (lastButtonState2 && !button2)
    {   
        pin[pinIndex] = currentDigit;
        pinIndex++;
        Serial.print("PIN: ");
        if (pinIndex == 4)
        {  
            for (int i = 0; i < 4; i++)
            {
                if (pin[i] != correctPin[i])
                {
                    correct = false;
                    break;
                }
            }
            currentDigit = 0;
            if (correct)
            {
                Serial.println("Access Granted");
                mode = 1;
            }
            else
            {
                Serial.println("Access Denied");
                mode = 2;
            }
        for (int i = 0; i < 4; i++)
            {
                Serial.print(pin[i]);
            }
        }
        correct = true;
    }
    if (pinIndex > 3)
    {
        pinIndex = 0;
    }
    gpio_set_led(mode);

    lastButtonState2 = button2;
    lastButtonState = button1;
}