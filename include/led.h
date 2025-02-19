#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"
#include <stdio.h>

#define LED_PIN PICO_DEFAULT_LED_PIN

void toggleLED(unsigned int period);

#endif // LED_H