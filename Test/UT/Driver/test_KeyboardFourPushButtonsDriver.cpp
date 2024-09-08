#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "main.h"
#include "stm32f1xx_hal_gpio.h"
#include "Driver/Inc/KeyboardFourPushButtonsDriver.hpp"

using namespace testing;
using namespace Driver;

// Global pointer to the MockHAL instance
MockHAL *mockHAL = nullptr;

// Test fixture class for KeyboardFourPushButtonsDriver
class KeyboardFourPushButtonsDriverTest : public ::testing::Test
{
protected:
    KeyboardFourPushButtonsDriver driver;
    MockHAL mockHALInstance;

    void SetUp() override
    {
        // Set the global mockHAL pointer to this instance
        mockHAL = &mockHALInstance;

        // Reset the driver to the initial state before each test
        driver.reset();
    }

    void TearDown() override
    {
        // Clean up the global pointer after each test
        mockHAL = nullptr;
    }
};

// Test the initialize method
TEST_F(KeyboardFourPushButtonsDriverTest, InitializeTest)
{
    EXPECT_TRUE(driver.initialize()); // Use public initialize method
    EXPECT_EQ(driver.getState(), DriverState::State::Initialized);
}

// Test the start method
TEST_F(KeyboardFourPushButtonsDriverTest, StartTest)
{
    driver.initialize();
    EXPECT_TRUE(driver.start()); // Use public start method
    EXPECT_EQ(driver.getState(), DriverState::State::Running);
}

// Test the stop method
TEST_F(KeyboardFourPushButtonsDriverTest, StopTest)
{
    driver.initialize();
    driver.start();
    EXPECT_TRUE(driver.stop()); // Use public stop method
    EXPECT_EQ(driver.getState(), DriverState::State::Stop);
}

// Test the reset method
TEST_F(KeyboardFourPushButtonsDriverTest, ResetTest)
{
    driver.initialize();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset()); // Use public reset method
    EXPECT_EQ(driver.getState(), DriverState::State::Reset);
}

// Test that tick updates the key states when running
TEST_F(KeyboardFourPushButtonsDriverTest, TickUpdatesKeyStatesWhenRunning)
{
    driver.initialize();
    driver.start();

    // Set expectations for HAL_GPIO_ReadPin to return GPIO_PIN_SET
    EXPECT_CALL(mockHALInstance, HAL_GPIO_ReadPin(_, _))
        .Times(driver.AmountOfKeys)
        .WillRepeatedly(Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    for (uint8_t i = 0u; i < driver.AmountOfKeys; i++)
    {
        EXPECT_EQ(driver.getKeyState(static_cast<KeyboardKeyIdentifier>(i)), KeyboardKeyState::NotPressed);
    }
}

// Test that tick does nothing when not running
TEST_F(KeyboardFourPushButtonsDriverTest, TickDoesNothingWhenNotRunning)
{
    // No expectation since HAL_GPIO_ReadPin should not be called
    EXPECT_FALSE(driver.tick());

    for (uint8_t i = 0u; i < driver.AmountOfKeys; i++)
    {
        EXPECT_EQ(driver.getKeyState(static_cast<KeyboardKeyIdentifier>(i)), KeyboardKeyState::DriverNotOperational);
    }
}

// Test handling asking for incorrect key
TEST_F(KeyboardFourPushButtonsDriverTest, GetKeyStateNothingWhenIncorrectKey)
{
    driver.initialize();
    driver.start();

    // Set expectations for HAL_GPIO_ReadPin to return GPIO_PIN_SET
    EXPECT_CALL(mockHALInstance, HAL_GPIO_ReadPin(_, _))
        .Times(driver.AmountOfKeys)
        .WillRepeatedly(Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    uint8_t incorrectKey = driver.AmountOfKeys;
    EXPECT_EQ(driver.getKeyState(static_cast<KeyboardKeyIdentifier>(incorrectKey)), KeyboardKeyState::UnknownKeyAsked);
}
