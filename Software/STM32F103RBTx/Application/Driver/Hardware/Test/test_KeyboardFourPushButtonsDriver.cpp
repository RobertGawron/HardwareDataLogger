#include "stm32f1xx_hal_gpio.h"
#include "Driver/Interfaces/KeyboardKeyIdentifier.hpp"
#include "Driver/Interfaces/KeyboardKeyState.hpp"
#include "Driver/Hardware/Inc/KeyboardFourPushButtonsDriver.hpp"
#include "Driver/Interfaces/DriverState.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>

class MockHAL_GPIO;

// Define the mockHAL_GPIO pointer expected by HAL_GPIO_ReadPin wrapper
MockHAL_GPIO *mockHAL_GPIO = nullptr;

class KeyboardFourPushButtonsDriverTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        mockHAL_GPIO = &mockHALInstance;
    }

    void TearDown() override
    {
        mockHAL_GPIO = nullptr;
    }

    // Getter for accessing private member
    MockHAL_GPIO &getMockHALInstance() { return mockHALInstance; }

private:
    MockHAL_GPIO mockHALInstance;
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
    EXPECT_CALL(getMockHALInstance(), HAL_GPIO_ReadPin(::testing::_, ::testing::_))
        .Times(Driver::KeyboardFourPushButtonsDriver::AmountOfKeys)
        .WillRepeatedly(::testing::Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    for (std::uint8_t i = 0u; i < Driver::KeyboardFourPushButtonsDriver::AmountOfKeys; i++)
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

    for (std::uint8_t i = 0u; i < Driver::KeyboardFourPushButtonsDriver::AmountOfKeys; i++)
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
    EXPECT_CALL(getMockHALInstance(), HAL_GPIO_ReadPin(::testing::_, ::testing::_))
        .Times(Driver::KeyboardFourPushButtonsDriver::AmountOfKeys)
        .WillRepeatedly(::testing::Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    const std::uint8_t incorrectKey = Driver::KeyboardFourPushButtonsDriver::AmountOfKeys;
    EXPECT_EQ(driver.getKeyState(static_cast<Driver::KeyboardKeyIdentifier>(incorrectKey)), Driver::KeyboardKeyState::UnknownKeyAsked);
}
