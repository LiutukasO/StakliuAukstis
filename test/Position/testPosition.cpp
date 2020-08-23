#if defined(ARDUINO) && defined(UNIT_TEST)

#include <unity.h>
#include <Arduino.h>
#include <Position.h>

unsigned char stepsPerRound = 16;
float milimetersPerRound    = 0.2;
unsigned char maxMilimeters = 250;

Position* position;

void test_getMilimetersPerStep_ShouldSucceed() {
    TEST_ASSERT_EQUAL_INT(0.0125, position->getMilimetersPerStep());
}

void test_milimetersToSteps_ShouldSucceed() {
    TEST_ASSERT_EQUAL_INT(0, position->milimetersToSteps(0));
    TEST_ASSERT_EQUAL_INT(80, position->milimetersToSteps(1));
    TEST_ASSERT_EQUAL_INT(-80, position->milimetersToSteps(-1));
    TEST_ASSERT_EQUAL_INT(1600, position->milimetersToSteps(20));
    TEST_ASSERT_EQUAL_INT(-1600, position->milimetersToSteps(-20));
}

void test_fitPositionToValidRange_ShouldSucceed() {
    TEST_ASSERT_EQUAL_INT(0, position->fitPositionToValidRange(0));
    TEST_ASSERT_EQUAL_INT(0, position->fitPositionToValidRange(-10));
    TEST_ASSERT_EQUAL_INT(10, position->fitPositionToValidRange(10));
    TEST_ASSERT_EQUAL_INT(20000, position->fitPositionToValidRange(25000));
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    position = new Position(stepsPerRound, milimetersPerRound, maxMilimeters);
    RUN_TEST(test_getMilimetersPerStep_ShouldSucceed);
    RUN_TEST(test_fitPositionToValidRange_ShouldSucceed);
    UNITY_END();
}

void loop(){
}

#endif