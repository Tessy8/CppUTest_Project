#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include <stdio.h>
#include "pico/stdlib.h"

int main(int ac, char ** av)
{
    stdio_init_all();
    sleep_ms(10000);
    printf("Running CppUTest...");

    const char * fav[5] = {"led_test", "-c", "-v", "-g", "led_test_group"};
    int res = CommandLineTestRunner::RunAllTests(5, fav);
    printf("Runner returned %d\n", res);
    
    // return CommandLineTestRunner::RunAllTests(ac, av);
}