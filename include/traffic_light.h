#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <stdio.h>
#include "pico/stdlib.h"

#define RED_LED_PIN 20
#define GREEN_LED_PIN 21
#define YELLOW_LED_PIN 22
#define BUTTON_PIN 5
#define MIN_LIMIT 10000
#define MAX_LIMIT 60000

typedef enum
{
    RED,
    GREEN,
    YELLOW
}traffic_light_state_t;

void setTrafficLightState(traffic_light_state_t state);
traffic_light_state_t runTrafficLight(void);
void startYellowTransition(void);
bool trafficLightButtonPressed(void);
void completeYellowTransitionToRed(uint16_t yellowToRedDuration);
uint16_t holdOnBeforeGreen(uint16_t redToGreenDuration);

#endif // TRAFFIC_LIGHT_H