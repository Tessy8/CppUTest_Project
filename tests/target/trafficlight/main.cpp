#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "main.h"

int main(int ac, char ** av)
{
    stdio_init_all();
    sleep_ms(10000);
    printf("Running CppUTest...\n");

    const char * fav[5] = {"trafficlight_test", "-c", "-v", "-g", "TrafficLightGroup"};
    int res = CommandLineTestRunner::RunAllTests(5, fav);
    printf("Runner returned %d\n", res);
    
    // return CommandLineTestRunner::RunAllTests(ac, av);
}