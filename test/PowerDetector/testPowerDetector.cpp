//#if defined(ARDUINO) && defined(UNIT_TEST)

#include <unity.h>
#include <Arduino.h>
#include <PowerDetector.h>

unsigned char powerControlerPin = A1;
unsigned char powerDetectorPin  = A0;

PowerDetector* powerDetector = new PowerDetector(powerDetectorPin);

void powerOn(){
    analogWrite(powerControlerPin, 1023);
    delay(100);
}

void powerOff(){
    analogWrite(powerControlerPin, 0);
    delay(100);
}

void test_isPowerOn_WhenDetectorPinHasValue1023_ShouldReturnTrue() {
    powerOn();
    TEST_ASSERT_GREATER_THAN(1020, analogRead(powerControlerPin));
    TEST_ASSERT_GREATER_THAN(1020, analogRead(powerDetectorPin));
    TEST_ASSERT_TRUE(powerDetector->isPowerOn());
}

void test_isPowerOn_WhenDetectorPinHasValue0_ShouldReturnFalse() {
    powerOff();
    TEST_ASSERT_LESS_THAN(1020, analogRead(powerControlerPin));
    TEST_ASSERT_LESS_THAN(1020, analogRead(powerDetectorPin));
    TEST_ASSERT_FALSE(powerDetector->isPowerOn());
}

void setup() {
    Serial.begin(115200);

    delay(2000);
    UNITY_BEGIN();
    pinMode(powerControlerPin, OUTPUT);
    RUN_TEST(test_isPowerOn_WhenDetectorPinHasValue1023_ShouldReturnTrue);
    RUN_TEST(test_isPowerOn_WhenDetectorPinHasValue0_ShouldReturnFalse);
    UNITY_END();
}

void loop(){
}

//#endif