#include <Arduino.h>
#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
#include "oled.h"
#include "lock_state.h"

int lastButtonState = 1;
int lastButtonState2 = 1;
int pin[4] = {1, 2, 3, 4};
int correctPin[4] = {1, 2, 3, 4};
int pinIndex = 0;
int currentDigit = 0;
bool correct = true;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
const unsigned long debounceDelay = 200;


LockState state = LOCKED;
LockState lastState = LOCKED;
int lastPinIndex = 0;
unsigned long state_start_time;

void setup()
{   
    gpio_init();
    oled_init();
    oled_show_state(state, pinIndex, pin);
    Serial.begin(9600);
}

void loop()
{
    int button1 = PIND & (1 << PIND2);
    int button2 = PIND & (1 << PIND6);

    if (lastButtonState && !button1 && millis() - lastDebounceTime1 > debounceDelay)
    {   
        lastDebounceTime1 = millis();
        currentDigit++;
    }

    if (currentDigit > 9)
    {
        currentDigit = 0;
    }
    if (lastButtonState2 && !button2 && millis() - lastDebounceTime2 > debounceDelay)
    {   
        pin[pinIndex] = currentDigit;
        pinIndex++;
        lastDebounceTime2 = millis();
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
    if (state != LOCKED && timer_expired(state_start_time, 2000))
    {
        state = LOCKED;
    }
    gpio_set_led(state);
    if (state != lastState || pinIndex != lastPinIndex)
    {
        oled_show_state(state, pinIndex, pin);

        lastState = state;
        lastPinIndex = pinIndex;
    }

    lastButtonState2 = button2;
    lastButtonState = button1;
}