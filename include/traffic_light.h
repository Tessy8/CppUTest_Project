#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

typedef enum
{
    RED,
    GREEN,
    YELLOW
}traffic_light_state_t;

void setTrafficLightState(traffic_light_state_t state);
traffic_light_state_t runTrafficLight(void);
void trafficLightButtonPressed(void);

#endif // TRAFFIC_LIGHT_H