#include <Arduino.h>
#include <avr/io.h>

#include "gpio.h"
#include "timer.h"
#include "oled.h"
#include "lock_state.h"
#include "eeprom.h"
#include "servo.h"

int pin[4] = {1, 2, 3, 4};
int correctPin[4] = {1, 2, 3, 4};
int lastButtonState = 1;
int lastButtonState2 = 1;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;

const unsigned long debounceDelay = 200;

int pinIndex = 0;
int currentDigit = 0;

bool correct = true;
bool oldPinVerified = false;

unsigned long button2PressTime = 0;
const unsigned long longPressDelay = 2000;

LockState state = LOCKED;
LockState lastState = LOCKED;

int lastPinIndex = 0;

unsigned long state_start_time = 0;

void setup()
{
    gpio_init();

    servo_init();

    oled_init();

    eeprom_read_pin(correctPin);

    gpio_set_led(LOCKED);

    oled_show_state(
        state,
        pinIndex,
        pin,
        oldPinVerified
    );

    Serial.begin(9600);
}

void loop()
{
    int button1 = PIND & (1 << PIND2);
    int button2 = PIND & (1 << PIND6);

    if (!button2 && button2PressTime == 0)
    {
        button2PressTime = millis();
    }

    if (
        !button2 &&
        button2PressTime != 0 &&
        millis() - button2PressTime >= longPressDelay &&
        state == LOCKED
    )
    {
        state = CHANGE_PIN;

        pinIndex = 0;
        currentDigit = 0;

        oldPinVerified = false;

        correct = true;

        button2PressTime = 0;

        for (int i = 0; i < 4; i++)
        {
            pin[i] = 0;
        }
    }

    if (button2)
    {
        button2PressTime = 0;
    }

    if (
        lastButtonState &&
        !button1 &&
        millis() - lastDebounceTime1 > debounceDelay
    )
    {
        lastDebounceTime1 = millis();

        currentDigit++;

        if (currentDigit > 9)
        {
            currentDigit = 0;
        }
    }

    if (
        lastButtonState2 &&
        !button2 &&
        millis() - lastDebounceTime2 > debounceDelay
    )
    {
        lastDebounceTime2 = millis();

        pin[pinIndex] = currentDigit;

        pinIndex++;

        currentDigit = 0;

        if (pinIndex == 4)
        {
            if (state == CHANGE_PIN)
            {

                if (!oldPinVerified)
                {
                    correct = true;

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
                        Serial.println("Old PIN correct");

                        oldPinVerified = true;

                        pinIndex = 0;
                        currentDigit = 0;

                        for (int i = 0; i < 4; i++)
                        {
                            pin[i] = 0;
                        }
                    }
                    else
                    {
                        Serial.println("Old PIN incorrect");

                        state = LOCKED;

                        pinIndex = 0;
                        currentDigit = 0;

                        oldPinVerified = false;

                        for (int i = 0; i < 4; i++)
                        {
                            pin[i] = 0;
                        }
                    }
                }

                else
                {
                    Serial.println("New PIN saved");

                    for (int i = 0; i < 4; i++)
                    {
                        correctPin[i] = pin[i];
                    }

                    eeprom_write_pin(correctPin);

                    state = LOCKED;

                    pinIndex = 0;
                    currentDigit = 0;

                    oldPinVerified = false;

                    for (int i = 0; i < 4; i++)
                    {
                        pin[i] = 0;
                    }
                }
            }

            else
            {
                correct = true;

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
                    Serial.println("Correct PIN");

                    state = GRANTED;

                    state_start_time = millis();

                    servo_open();
                }

                else
                {
                    Serial.println("Access Denied");

                    state = DENIED;

                    state_start_time = millis();
                }
            }

            pinIndex = 0;
        }


        correct = true;
    }

    if (
        (state == GRANTED || state == DENIED) &&
        timer_expired(state_start_time, 2000)
    )
    {
        state = LOCKED;

        servo_close();

        pinIndex = 0;
        currentDigit = 0;

        for (int i = 0; i < 4; i++)
        {
            pin[i] = 0;
        }
    }

    gpio_set_led(state);

    if (
        state != lastState ||
        pinIndex != lastPinIndex ||
        oldPinVerified
    )
    {
        oled_show_state(
            state,
            pinIndex,
            pin,
            oldPinVerified
        );

        lastState = state;
        lastPinIndex = pinIndex;
    }
    lastButtonState = button1;
    lastButtonState2 = button2;
}