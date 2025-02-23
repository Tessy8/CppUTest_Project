#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#define RED_LED_PIN 20
#define GREEN_LED_PIN 21
#define YELLOW_LED_PIN 22
#define BUTTON_PIN 5
#define MIN_LIMIT 10
#define MAX_LIMIT 60

typedef enum
{
    RED,
    GREEN,
    YELLOW
}traffic_light_state_t;

void setTrafficLightState(traffic_light_state_t state);
traffic_light_state_t runTrafficLight(static bool buttonPressed);
bool trafficLightButtonPressed(void);
void startYellowTransition(void);
void completeYellowTransitionToRed(uint8_t yellowToRedDuration);
uint8_t holdOnBeforeGreen(uint8_t redToGreenDuration);

#endif // TRAFFIC_LIGHT_H