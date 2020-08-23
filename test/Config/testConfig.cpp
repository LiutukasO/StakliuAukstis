#if defined(ARDUINO) && defined(UNIT_TEST)

#include <unity.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <Config.h>

void test_FirstTimeLoadDefaultConfig_ShouldSucceed() {
    unsigned char maxWriteCount = 2;
    Config* config = new Config(maxWriteCount);
    TEST_ASSERT_EQUAL_UINT(0, config->getReadFromByte());
    TEST_ASSERT_EQUAL_UINT(1, config->getWriteCounter());
    TEST_ASSERT_EQUAL_FLOAT(0, config->getPosition());
}

void test_SaveConfigToEEPROMSecondTime_ShouldSucceed() {
    unsigned char maxWriteCount = 2;
    Config* config = new Config(maxWriteCount);
    TEST_ASSERT_EQUAL_UINT(0, config->getReadFromByte());
    TEST_ASSERT_EQUAL_UINT(1, config->getWriteCounter());
    TEST_ASSERT_EQUAL_INT(0, config->getPosition());

    config->setPosition(123);
    TEST_ASSERT_TRUE(config->save());

    config = new Config(maxWriteCount);
    TEST_ASSERT_EQUAL_UINT(0, config->getReadFromByte());
    TEST_ASSERT_EQUAL_UINT(2, config->getWriteCounter());
    TEST_ASSERT_EQUAL_INT(123, config->getPosition());
}


void test_WhenSaveConfigToEEPROMThirdTime_ShouldSaveConfigInNextEEPROMDataBlock() {
    unsigned char maxWriteCount = 2;
    Config* config = new Config(maxWriteCount);
    TEST_ASSERT_EQUAL_UINT(0, config->getReadFromByte());
    TEST_ASSERT_EQUAL_UINT(2, config->getWriteCounter());
    TEST_ASSERT_EQUAL_INT(123, config->getPosition());

    config->setPosition(456);
    TEST_ASSERT_TRUE(config->save());

    TEST_ASSERT_EQUAL_UINT(11, config->getReadFromByte());
    TEST_ASSERT_EQUAL_UINT(1, config->getWriteCounter());
    TEST_ASSERT_EQUAL_INT(456, config->getPosition());
}

void test_WhenReadConfigFromNextEEPROMDataBlock_ShouldSucceed() {
    unsigned char maxWriteCount = 2;
    Config* config = new Config(maxWriteCount);
    TEST_ASSERT_EQUAL_UINT(11, config->getReadFromByte());
    TEST_ASSERT_EQUAL_UINT(1, config->getWriteCounter());
    TEST_ASSERT_EQUAL_INT(456, config->getPosition());
}

void clearEEPROM(){
    for (unsigned int i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0);
    }
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    clearEEPROM();
    RUN_TEST(test_FirstTimeLoadDefaultConfig_ShouldSucceed);
    RUN_TEST(test_SaveConfigToEEPROMSecondTime_ShouldSucceed);
    RUN_TEST(test_WhenSaveConfigToEEPROMThirdTime_ShouldSaveConfigInNextEEPROMDataBlock);
    RUN_TEST(test_WhenReadConfigFromNextEEPROMDataBlock_ShouldSucceed);
    UNITY_END();
}

void loop(){
}

#endif