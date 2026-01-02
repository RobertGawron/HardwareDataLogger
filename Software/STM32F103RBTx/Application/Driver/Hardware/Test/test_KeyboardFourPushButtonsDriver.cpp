#include "stm32f1xx_hal_gpio.h"
#include "Driver/Interface/KeyIdentifier.hpp"
#include "Driver/Interface/KeyState.hpp"
#include "Driver/Hardware/Inc/KeyboardDriver.hpp"
#include "Driver/Interface/DriverComponent.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>

class MockHAL_GPIO;

// Define the mockHAL_GPIO pointer expected by HAL_GPIO_ReadPin wrapper
MockHAL_GPIO *mockHAL_GPIO = nullptr;

class KeyboardDriverTest : public ::testing::Test
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
TEST_F(KeyboardDriverTest, InitializeTest)
{
    Driver::KeyboardDriver driver;
    EXPECT_TRUE(driver.init()); // Use public initialize method
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Initialized);
}

// Test the start method
TEST_F(KeyboardDriverTest, StartTest)
{
    Driver::KeyboardDriver driver;
    driver.init();
    EXPECT_TRUE(driver.start()); // Use public start method
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Running);
}

// Test the stop method
TEST_F(KeyboardDriverTest, StopTest)
{
    Driver::KeyboardDriver driver;
    driver.init();
    driver.start();
    EXPECT_TRUE(driver.stop()); // Use public stop method
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Stop);
}

// Test the reset method
TEST_F(KeyboardDriverTest, ResetTest)
{
    Driver::KeyboardDriver driver;
    driver.init();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset()); // Use public reset method
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Reset);
}

// Test that tick updates the key states when running
TEST_F(KeyboardDriverTest, TickUpdatesKeyStatesWhenRunning)
{
    Driver::KeyboardDriver driver;
    driver.init();
    driver.start();

    // Set expectations for HAL_GPIO_ReadPin to return GPIO_PIN_SET
    EXPECT_CALL(getMockHALInstance(), HAL_GPIO_ReadPin(::testing::_, ::testing::_))
        .Times(Driver::KeyboardDriver::AmountOfKeys)
        .WillRepeatedly(::testing::Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    for (std::uint8_t i = 0U; i < Driver::KeyboardDriver::AmountOfKeys; i++)
    {
        EXPECT_EQ(driver.getKeyState(static_cast<Driver::KeyIdentifier>(i)), Driver::KeyState::NotPressed);
    }
}

// Test that tick does nothing when not running
TEST_F(KeyboardDriverTest, TickDoesNothingWhenNotRunning)
{
    Driver::KeyboardDriver driver;
    // No expectation since HAL_GPIO_ReadPin should not be called
    EXPECT_FALSE(driver.tick());

    for (std::uint8_t i = 0U; i < Driver::KeyboardDriver::AmountOfKeys; i++)
    {
        EXPECT_EQ(driver.getKeyState(static_cast<Driver::KeyIdentifier>(i)), Driver::KeyState::DriverNotOperational);
    }
}

// Test handling asking for incorrect key
TEST_F(KeyboardDriverTest, GetKeyStateNothingWhenIncorrectKey)
{
    Driver::KeyboardDriver driver;
    driver.init();
    driver.start();

    // Set expectations for HAL_GPIO_ReadPin to return GPIO_PIN_SET
    EXPECT_CALL(getMockHALInstance(), HAL_GPIO_ReadPin(::testing::_, ::testing::_))
        .Times(Driver::KeyboardDriver::AmountOfKeys)
        .WillRepeatedly(::testing::Return(GPIO_PIN_SET));

    EXPECT_TRUE(driver.tick());

    const std::uint8_t incorrectKey = Driver::KeyboardDriver::AmountOfKeys;
    EXPECT_EQ(driver.getKeyState(static_cast<Driver::KeyIdentifier>(incorrectKey)), Driver::KeyState::UnknownKeyAsked);
}
