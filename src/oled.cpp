#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "oled.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void oled_init()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.clearDisplay();
    display.display();
}

void oled_clear()
{
    display.clearDisplay();
    display.display();
}

void oled_show_state(
    LockState state,
    int pinIndex,
    int pin[4],
    bool oldPinVerified
)
{
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    switch (state)
    {
        case LOCKED:
            display.setTextSize(2);
            display.println("Enter PIN");

            display.setTextSize(1);

            for (int i = 0; i < 4; i++)
            {
                if (i < pinIndex)
                {
                    display.print("*");
                }
                else
                {
                    display.print("_");
                }

                display.print(" ");
            }
            break;

        case GRANTED:
            display.setTextSize(2);
            display.println("GRANTED");
            break;

        case DENIED:
            display.setTextSize(2);
            display.println("DENIED");
            break;

        case CHANGE_PIN:
            display.setTextSize(2);

            if (!oldPinVerified)
            {
                display.println("OLD PIN");
            }
            else
            {
                display.println("NEW PIN");
            }

            display.setTextSize(1);

            for (int i = 0; i < 4; i++)
            {
                if (i < pinIndex)
                {
                    display.print("*");
                }
                else
                {
                    display.print("_");
                }

                display.print(" ");
            }
            break;
    }

    display.display();
}