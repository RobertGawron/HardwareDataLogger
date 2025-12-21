
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "main.h"
#include "stm32f1xx_hal_gpio.h"
#include "Driver/Inc/KeyboardFourPushButtonsDriver.hpp"

using namespace testing;

class MockHAL_GPIO;

// Define the mockHAL_GPIO pointer expected by HAL_GPIO_ReadPin wrapper
MockHAL_GPIO *mockHAL_GPIO = nullptr;

class KeyboardFourPushButtonsDriverTest : public ::testing::Test {
protected:
    MockHAL_GPIO mockHALInstance;

    void SetUp() override {
        mockHAL_GPIO = &mockHALInstance;
    }

    void TearDown() override {
        mockHAL_GPIO = nullptr;
    }
};

// Test the initialize method
TEST_F(KeyboardFourPushButtonsDriverTest, InitializeTest)
{
    Driver::KeyboardFourPushButtonsDriver driver;
    EXPECT_TRUE(driver.initialize()); // Use public initialize method
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Initialized);
}

// Test the start method
TEST_F(KeyboardFourPushButtonsDriverTest, StartTest)
{
    Driver::KeyboardFourPushButtonsDriver driver;
    driver.initialize();
    EXPECT_TRUE(driver.start()); // Use public start method
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Running);
}

// Test the stop method
TEST_F(KeyboardFourPushButtonsDriverTest, StopTest)
{
    Driver::KeyboardFourPushButtonsDriver driver;
    driver.initialize();
    driver.start();
    EXPECT_TRUE(driver.stop()); // Use public stop method
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Stop);
}

// Test the reset method
TEST_F(KeyboardFourPushButtonsDriverTest, ResetTest)
{
    Driver::KeyboardFourPushButtonsDriver driver;
    driver.initialize();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset()); // Use public reset method
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Reset);
}

// Test that tick updates the key states when running
TEST_F(KeyboardFourPushButtonsDriverTest, TickUpdatesKeyStatesWhenRunning)
{
    Driver::KeyboardFourPushButtonsDriver driver;
    driver.initialize();
    driver.start();

    // Set expectations for HAL_GPIO_ReadPin to return GPIO_PIN_SET
    EXPECT_CALL(mockHALInstance, HAL_GPIO_ReadPin(_, _))
        .Times(driver.AmountOfKeys)
        .WillRepeatedly(Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    for (std::uint8_t i = 0u; i < driver.AmountOfKeys; i++)
    {
        EXPECT_EQ(driver.getKeyState(static_cast<Driver::KeyboardKeyIdentifier>(i)), Driver::KeyboardKeyState::NotPressed);
    }
}

// Test that tick does nothing when not running
TEST_F(KeyboardFourPushButtonsDriverTest, TickDoesNothingWhenNotRunning)
{
    Driver::KeyboardFourPushButtonsDriver driver;
    // No expectation since HAL_GPIO_ReadPin should not be called
    EXPECT_FALSE(driver.tick());

    for (std::uint8_t i = 0u; i < driver.AmountOfKeys; i++)
    {
        EXPECT_EQ(driver.getKeyState(static_cast<Driver::KeyboardKeyIdentifier>(i)), Driver::KeyboardKeyState::DriverNotOperational);
    }
}

// Test handling asking for incorrect key
TEST_F(KeyboardFourPushButtonsDriverTest, GetKeyStateNothingWhenIncorrectKey)
{
    Driver::KeyboardFourPushButtonsDriver driver;
    driver.initialize();
    driver.start();

    // Set expectations for HAL_GPIO_ReadPin to return GPIO_PIN_SET
    EXPECT_CALL(mockHALInstance, HAL_GPIO_ReadPin(_, _))
        .Times(driver.AmountOfKeys)
        .WillRepeatedly(Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    std::uint8_t incorrectKey = driver.AmountOfKeys;
    EXPECT_EQ(driver.getKeyState(static_cast<Driver::KeyboardKeyIdentifier>(incorrectKey)), Driver::KeyboardKeyState::UnknownKeyAsked);
}
