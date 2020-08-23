//#if defined(ARDUINO) && defined(UNIT_TEST)

#include <unity.h>
#include <Arduino.h>
#include <Display.h>

uint8_t pinClk = 8;
uint8_t pinDIO = 7;
float milimetersPerStep = 0.0125; // 0.0125mm (80 steps per mm)

void test_setPosition_ShouldSucceed() {
    Display* display = new Display(pinClk, pinDIO, milimetersPerStep);
    unsigned long time = display->getUpdateTime();
    TEST_ASSERT_EQUAL_INT(0, display->getPosition());
    TEST_ASSERT_FALSE(display->isNeedToShow());

    display->setPosition(0);
    TEST_ASSERT_FALSE(display->isNeedToShow());

    display->setPosition(180);
    TEST_ASSERT_TRUE(display->isNeedToShow());
    TEST_ASSERT_EQUAL_INT(180, display->getPosition());
    TEST_ASSERT_EQUAL_UINT(time, display->getUpdateTime());
}

void test_getMilimeters_When180PositionGiven_ShouldReturnMilimeters() {
    Display* display = new Display(pinClk, pinDIO, milimetersPerStep);
    unsigned long time = display->getUpdateTime();

    display->setPosition(180);
    TEST_ASSERT_TRUE(display->isNeedToShow());
    TEST_ASSERT_EQUAL_INT(180, display->getPosition());
    TEST_ASSERT_EQUAL_FLOAT(2.25, display->getHeightInMilimeters());

    display->setPosition(0);
    TEST_ASSERT_EQUAL_INT(0, display->getPosition());
    TEST_ASSERT_EQUAL_FLOAT(0, display->getHeightInMilimeters());

    display->setPosition(1);
    TEST_ASSERT_EQUAL_INT(1, display->getPosition());
    TEST_ASSERT_EQUAL_FLOAT(0.0125, display->getHeightInMilimeters());

    display->setPosition(32767);
    TEST_ASSERT_EQUAL_INT(32767, display->getPosition());
    TEST_ASSERT_EQUAL_FLOAT(409.5875, display->getHeightInMilimeters());

    TEST_ASSERT_EQUAL_UINT(time, display->getUpdateTime());
}

void test_show_WhenUpdateExecuted_ShouldSucceed() {
    Display* display = new Display(pinClk, pinDIO, milimetersPerStep);
    unsigned long time = display->getUpdateTime();
    TEST_ASSERT_FALSE(display->isNeedToShow());
    TEST_ASSERT_FALSE(display->update());
    TEST_ASSERT_EQUAL_UINT(time, display->getUpdateTime());

    display->setPosition(180);
    TEST_ASSERT_TRUE(display->isNeedToShow());
    TEST_ASSERT_TRUE(display->update());
    TEST_ASSERT_FALSE(display->isNeedToShow());
    TEST_ASSERT_TRUE(time < display->getUpdateTime());

    time = display->getUpdateTime();
    TEST_ASSERT_FALSE(display->update());
    TEST_ASSERT_FALSE(display->isNeedToShow());
    TEST_ASSERT_EQUAL_UINT(time, display->getUpdateTime());

    display->setPosition(100);
    TEST_ASSERT_TRUE(display->isNeedToShow());
    TEST_ASSERT_FALSE(display->update());
    TEST_ASSERT_TRUE(display->isNeedToShow());
    TEST_ASSERT_EQUAL_UINT(time, display->getUpdateTime());
    delay(300);
    TEST_ASSERT_TRUE(display->update());
    TEST_ASSERT_FALSE(display->isNeedToShow());
    TEST_ASSERT_TRUE(time < display->getUpdateTime());
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_setPosition_ShouldSucceed);
    RUN_TEST(test_getMilimeters_When180PositionGiven_ShouldReturnMilimeters);
    RUN_TEST(test_show_WhenUpdateExecuted_ShouldSucceed);
    UNITY_END();
}

void loop(){
}

//#endif