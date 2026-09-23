#include <EEPROM.h>
#include "eeprom.h"

void eeprom_write_pin(int pin[4]) 
{
    for (int i = 0; i < 4; i++) 
    {
        EEPROM.write(i, pin[i]);
    }
}
void eeprom_read_pin(int pin[4]) 
{
    for (int i = 0; i < 4; i++) 
    {
        pin[i] = EEPROM.read(i);
    }
}