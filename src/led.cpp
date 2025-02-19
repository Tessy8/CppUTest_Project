#include "led.h"

void toggleLED(unsigned int period){
    gpio_put(LED_PIN, 1); // Turn LED ON
    sleep_ms(period);
    gpio_put(LED_PIN, 0); // Turn LED OFF
    sleep_ms(period);
}