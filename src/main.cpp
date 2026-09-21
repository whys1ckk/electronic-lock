#include <Arduino.h>
#include <avr/io.h>
#include "gpio.h"

int lastButtonState = 1;
int lastButtonState2 = 1;
int pin[4] = {1, 2, 3, 4};
int correctPin[4] = {1, 2, 3, 4};
int pinIndex = 0;
int currentDigit = 0;
bool correct = true;

enum LockState 
{
    LOCKED,
    GRANTED, 
    DENIED
};

LockState state = LOCKED;
unsigned long state_start_time;

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
                state = GRANTED;
                state_start_time = millis();
            }
            else
            {
                Serial.println("Access Denied");
                state = DENIED;
                state_start_time = millis();
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
    if (state != LOCKED && millis() - state_start_time >= 2000)
    {
        state = LOCKED;
    }
    gpio_set_led(state);

    lastButtonState2 = button2;
    lastButtonState = button1;
}