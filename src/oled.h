#ifndef OLED_H
#define OLED_H

#include "lock_state.h"

void oled_init();
void oled_clear();

void oled_show_state(
    LockState state,
    int pinIndex,
    int pin[4],
    bool oldPinVerified
);

#endif // OLED_H