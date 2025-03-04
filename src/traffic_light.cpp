#include "traffic_light.h"

static traffic_light_state_t currentState = RED;
static traffic_light_state_t nextState = currentState;
static bool buttonPressed = false;

namespace traffic {
    bool gpio_get(uint gpio, bool test) {
        if (test) {
            return true;
        }
        return ::gpio_get(gpio); 
    }
}

void setTrafficLightState(traffic_light_state_t state)
{
    traffic_light_state_t previousState;
    switch(state)
    {
        case RED:
            previousState = YELLOW;
            break;
        case YELLOW:
            previousState = GREEN;
            break;
        case GREEN:
            previousState = RED;
            break;
    }
    if (currentState == previousState)
    {
        nextState = state;
        runTrafficLight();
    }
}

traffic_light_state_t runTrafficLight(void)
{
    switch (nextState)
    {
        case RED:
            currentState = RED;
            gpio_put(RED_LED_PIN, 1);
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(YELLOW_LED_PIN, 0);
            break;
        case GREEN:
            currentState = GREEN;
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 1);
            gpio_put(YELLOW_LED_PIN, 0);
            break;
        case YELLOW:
            currentState = YELLOW;
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(YELLOW_LED_PIN, 1);
            break;
    }
    return currentState;
}

namespace traffic {
    bool trafficLightButtonPressed(void)
    {
        buttonPressed = (gpio_get(BUTTON_PIN, true) == 1);
        if (buttonPressed && currentState == GREEN)
        {
            return true;
        } else
        {
            return false;
        }
    }
} 
    
void startYellowTransition(void)
{
    setTrafficLightState(YELLOW);
}

void completeYellowTransitionToRed(uint16_t yellowToRedDuration)
{
    sleep_ms(yellowToRedDuration);
    setTrafficLightState(RED);
}

uint16_t holdOnBeforeGreen(uint16_t redToGreenDuration)
{
    if (redToGreenDuration < MIN_LIMIT)
    {
        redToGreenDuration = MIN_LIMIT;
    } else if (redToGreenDuration > MAX_LIMIT)
    {
        redToGreenDuration = MAX_LIMIT;
    }
    return redToGreenDuration;
}