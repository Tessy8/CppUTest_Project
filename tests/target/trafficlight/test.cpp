// test_traffic_light.cpp

#include "CppUTest/TestHarness.h"
#include "traffic_light.h"

extern "C" 
{
    int gpio_get(uint gpio)
    {
        // Simulate that the button is pressed by always returning 1
        return 1;
    }
}

TEST_GROUP(TrafficLightGroup)
{
    void setup()
    {
        // Runs before each test
        setTrafficLightState(RED); // Reset to RED before each test
    }
    
    void teardown()
    {
        // Runs after each test
    }
};

TEST(TrafficLightGroup, InitialStateIsRed)
{
    CHECK_EQUAL(RED, runTrafficLight()); // This checks that the traffic light starts in RED.
}

TEST(TrafficLightGroup, CorrectLightTransitions)
{
    // The light should start in RED
    CHECK_EQUAL(RED, runTrafficLight());

    setTrafficLightState(GREEN); // Transition: RED should change to GREEN
    CHECK_EQUAL(GREEN, runTrafficLight());

    setTrafficLightState(YELLOW); // Transition: GREEN should change to YELLOW
    CHECK_EQUAL(YELLOW, runTrafficLight());

    setTrafficLightState(RED); // Transition: YELLOW should change to RED
    CHECK_EQUAL(RED, runTrafficLight());
}

TEST(TrafficLightGroup, ButtonPressOnGreenGoesToYellowThenRed)
{
    // Start the light at GREEN
    setTrafficLightState(GREEN);
    CHECK_EQUAL(GREEN, runTrafficLight());

    // Simulate the pedestrian button press during GREEN
    CHECK_TRUE(trafficLightButtonPressed());

    // On the next run, we expect a transition to YELLOW
    startYellowTransition();
    CHECK_EQUAL(YELLOW, runTrafficLight());

    // Then the next run should bring it to RED
    completeYellowTransitionToRed();
    CHECK_EQUAL(RED, runTrafficLight());
}

TEST(TrafficLightGroup, ButtonPressOnYellowOrRed)
{
    // Start light at YELLOW
    setTrafficLightState(YELLOW);
    CHECK_EQUAL(YELLOW, runTrafficLight());

    // Simulate the pedestrian button press during YELLOW
    CHECK_FALSE(trafficLightButtonPressed());

    // Start light at RED
    setTrafficLightState(RED);
    CHECK_EQUAL(RED, runTrafficLight());

    // Simulate the pedestrian button press during RED
    CHECK_FALSE(trafficLightButtonPressed());

}

TEST(TrafficLightGroup, NoDirectJumps)
{
    // 1. Direct jump from RED to YELLOW should not occur.
    setTrafficLightState(RED);
    CHECK_EQUAL(RED, runTrafficLight()); // Confirm we start at RED.
    setTrafficLightState(YELLOW);         // Attempt an illegal jump.
    // Expect that the system does not transition to YELLOW.
    CHECK_EQUAL(RED, runTrafficLight());

    // 2. Direct jump from GREEN to RED should not occur.
    setTrafficLightState(GREEN);
    CHECK_EQUAL(GREEN, runTrafficLight()); // Confirm we are at GREEN.
    setTrafficLightState(RED);              // Attempt an illegal jump.
    // Expect that the system does not transition to RED.
    CHECK_EQUAL(GREEN, runTrafficLight());

    // 3. Direct jump from YELLOW to GREEN should not occur.
    setTrafficLightState(YELLOW);
    CHECK_EQUAL(YELLOW, runTrafficLight()); // Confirm we are at YELLOW.
    setTrafficLightState(GREEN);            // Attempt an illegal jump.
    // Expect that the system does not transition to GREEN.
    CHECK_EQUAL(YELLOW, runTrafficLight());
}

TEST(TrafficLightGroup, RedtoGreenLimits)
{
    CHECK_EQUAL(MIN_LIMIT, holdOnBeforeGreen(0));
    CHECK_EQUAL(30, holdOnBeforeGreen(30));
    CHECK_EQUAL(MAX_LIMIT, holdOnBeforeGreen(61));
}