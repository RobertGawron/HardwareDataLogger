#include "stm32f1xx_hal.h"
#include "Driver/Hardware/Inc/BrightnessDriver.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdint>

// Global pointer for production code access (MockTimer definition assumed in separate file)
extern MockTimer *mockTimer;

class BrightnessDriverTest : public ::testing::Test
{
private:
    // Encapsulated fields
    TIM_HandleTypeDef htim{};
    MockTimer mockTimerInstance;
    std::unique_ptr<Driver::BrightnessDriver> driver;

protected:
    void SetUp() override
    {
        mockTimer = &mockTimerInstance; // Assign the global mock instance
        driver = std::make_unique<Driver::BrightnessDriver>(htim);
    }

    void TearDown() override
    {
        mockTimer = nullptr; // Reset the global mock instance
    }

public:
    // Public Getters
    Driver::BrightnessDriver &getDriver() { return *driver; }
    MockTimer &getMockTimer() { return mockTimerInstance; }
    TIM_HandleTypeDef &getHtim() { return htim; }
};

// --- Test Cases ---

TEST_F(BrightnessDriverTest, InitializeShouldSucceed)
{
    // Expect the clock enable function to be called once
    EXPECT_CALL(getMockTimer(), __HAL_RCC_TIM3_CLK_ENABLE())
        .Times(1);

    // Expect the PWM initialization function to be called once
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_Init(::testing::_))
        .WillOnce(::testing::Return(HAL_OK));

    // Expect the PWM channel configuration function to be called once
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_ConfigChannel(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));

    EXPECT_TRUE(getDriver().init());
    EXPECT_TRUE(getDriver().isInState(Driver::DriverComponent::State::Initialized));
}

TEST_F(BrightnessDriverTest, StartShouldSucceed)
{
    // Ensure proper initialization is expected
    EXPECT_CALL(getMockTimer(), __HAL_RCC_TIM3_CLK_ENABLE()).Times(::testing::AtLeast(1));
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_Init(::testing::_)).WillOnce(::testing::Return(HAL_OK));
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_ConfigChannel(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));

    ASSERT_TRUE(getDriver().init());

    // Expectations for the start process
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_Start(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));
    EXPECT_CALL(getMockTimer(), __HAL_TIM_SET_COMPARE(::testing::_, ::testing::_, ::testing::_))
        .Times(::testing::AtLeast(1));

    EXPECT_TRUE(getDriver().start());
}

TEST_F(BrightnessDriverTest, StopShouldSucceed)
{
    // Arrange initialization and start calls
    EXPECT_CALL(getMockTimer(), __HAL_RCC_TIM3_CLK_ENABLE()).Times(::testing::AtLeast(1));
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_Init(::testing::_)).WillOnce(::testing::Return(HAL_OK));
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_ConfigChannel(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));
    ASSERT_TRUE(getDriver().init());

    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_Start(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));
    EXPECT_CALL(getMockTimer(), __HAL_TIM_SET_COMPARE(::testing::_, ::testing::_, ::testing::_))
        .Times(::testing::AtLeast(1));
    ASSERT_TRUE(getDriver().start());

    // Expect stop call
    EXPECT_CALL(getMockTimer(), HAL_TIM_PWM_Stop(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));

    // Act
    EXPECT_TRUE(getDriver().stop());

    // Assert
    EXPECT_TRUE(getDriver().isInState(Driver::DriverComponent::State::Stop));
}

TEST_F(BrightnessDriverTest, ResetShouldSucceed)
{
    EXPECT_TRUE(getDriver().reset());
    EXPECT_TRUE(getDriver().isInState(Driver::DriverComponent::State::Reset));
}

TEST_F(BrightnessDriverTest, SetBrightnessWithinValidRange)
{
    const std::uint8_t validBrightness = 50;
    const std::uint32_t expectedPulse = (validBrightness * 4799) / 100;

    EXPECT_CALL(getMockTimer(), __HAL_TIM_SET_COMPARE(&getHtim(), TIM_CHANNEL_2, expectedPulse))
        .Times(1)
        .WillOnce(::testing::Return());

    bool result = getDriver().setBrightness(validBrightness);
    EXPECT_TRUE(result);
}

TEST_F(BrightnessDriverTest, SetBrightnessOutsideValidRange)
{
    const std::uint8_t invalidBrightness = 101;

    // The set compare function should not be called
    EXPECT_CALL(getMockTimer(), __HAL_TIM_SET_COMPARE(::testing::_, ::testing::_, ::testing::_))
        .Times(0);

    bool result = getDriver().setBrightness(invalidBrightness);
    EXPECT_FALSE(result);
}
