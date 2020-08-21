#if defined(ARDUINO) && defined(UNIT_TEST)

#include "unity.h"
#include "Position.h"

float milimetersPerRound    = 0.2;
unsigned char stepsPerRound = 16;
unsigned int maxMilimeters  = 250;

Position* position = new Position(milimetersPerRound, stepsPerRound, maxMilimeters);

void testIncreaseBySteps() {
    position->setPosition(0);
    TEST_ASSERT_EQUAL_INT(0, position->getPosition());
    position->increaseBySteps(15);
    TEST_ASSERT_EQUAL_INT(15, position->getPosition());
    position->increaseBySteps(-5);
    TEST_ASSERT_EQUAL_INT(10, position->getPosition());
    position->increaseBySteps(-15);
    TEST_ASSERT_EQUAL_INT(0, position->getPosition());
    position->increaseBySteps(25000); // above max position (20`000)
    TEST_ASSERT_EQUAL_INT(20000, position->getPosition());
}

void getHeightInMilimeters_WhenPositionZeroGiven_ShouldReturnZeroMilimeters() {
    position->setPosition(0);
    TEST_ASSERT_EQUAL_INT(0, position->getPosition());
    float milimeters = position->getHeightInMilimeters();
    TEST_ASSERT_EQUAL_FLOAT(0, milimeters);
}

void getHeightInMilimeters_WhenPositionBelowZeroGiven_ShouldReturnZeroMilimeters() {
    position->setPosition(-10);
    TEST_ASSERT_EQUAL_INT(0, position->getPosition());
    float milimeters = position->getHeightInMilimeters();
    TEST_ASSERT_EQUAL_FLOAT(0, milimeters);
}

void getHeightInMilimeters_WhenPosition120Given_ShouldReturn1point5Milimeters() {
    position->setPosition(120);
    TEST_ASSERT_EQUAL_INT(120, position->getPosition());
    float milimeters = position->getHeightInMilimeters();
    TEST_ASSERT_EQUAL_FLOAT(1.5, milimeters);
}

void getHeightInMilimeters_WhenPositionAboveMaxGiven_ShouldReturn250Milimeters() {
    position->setPosition(0);
    position->increaseByMilimeters(300);
    TEST_ASSERT_EQUAL_INT(20000, position->getPosition());
    float milimeters = position->getHeightInMilimeters();
    TEST_ASSERT_EQUAL_FLOAT(250, milimeters);
}

void testgetHeightInMilimeters_WhenPosition100Given_ShouldReturnRoundedTo1point3Milimeters() {
    position->setPosition(100);
    TEST_ASSERT_EQUAL_INT(100, position->getPosition());
    float milimeters = position->getHeightInMilimeters();
    TEST_ASSERT_EQUAL_FLOAT(1.3, milimeters);
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(testIncreaseBySteps);
  RUN_TEST(getHeightInMilimeters_WhenPositionZeroGiven_ShouldReturnZeroMilimeters);
  RUN_TEST(getHeightInMilimeters_WhenPositionBelowZeroGiven_ShouldReturnZeroMilimeters);
  RUN_TEST(getHeightInMilimeters_WhenPosition120Given_ShouldReturn1point5Milimeters);
  RUN_TEST(getHeightInMilimeters_WhenPositionAboveMaxGiven_ShouldReturn250Milimeters);
  RUN_TEST(testgetHeightInMilimeters_WhenPosition100Given_ShouldReturnRoundedTo1point3Milimeters);
  UNITY_END();
}

void loop() {
}

#endif