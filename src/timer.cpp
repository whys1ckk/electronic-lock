#include <Arduino.h>
#include "timer.h"

bool timer_expired(unsigned long start_time, unsigned long duration)
{
    unsigned long current_time = millis();

    return (current_time - start_time) >= duration;
}