#include "pico/stdlib.h"
#include <stdio.h>
#include "led.h"

int main(void)
{
    stdio_init_all();
    // Initialize LED pin
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(true)
    {
        toggleLED(5000);
    }
    return 0;
}
