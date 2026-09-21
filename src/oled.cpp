#include <Arduino.h>
#include "oled.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

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
void oled_show_state(LockState state, int pinIndex, int pin[4]) 
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    switch (state) 
    {
        case LOCKED:
            display.println("Enter PIN");
            display.setTextSize(1);
            for (int i = 0; i < 4; i++) 
            {
                if (i < pinIndex) 
                {
                    display.print(pin[i]);
                } 
                else 
                {
                    display.print("_");
                }
                display.print(" ");
            }
            break;
        case GRANTED:
            display.println("GRANTED");
            break;
        case DENIED:
            display.println("DENIED");
            break;
    }
    display.display();
}