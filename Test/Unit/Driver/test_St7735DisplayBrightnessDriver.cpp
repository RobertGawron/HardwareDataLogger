#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "main.h"
// #include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal.h"

#include "Driver/Inc/St7735DisplayBrightnessDriver.hpp"

using namespace testing;
using namespace Driver;

MockTimer *mockTimer; // This allows the production code to access the mock

class St7735DisplayBrightnessDriverTest : public Test
{
protected:
    TIM_HandleTypeDef htim;
    St7735DisplayBrightnessDriver *driver;
    MockTimer mockTimerInstance;

    void SetUp() override
    {
        mockTimer = &mockTimerInstance; // Assign the global mock instance
        driver = new St7735DisplayBrightnessDriver(htim);
    }

    void TearDown() override
    {
        delete driver;
        mockTimer = nullptr; // Reset the global mock instance
    }
};

TEST_F(St7735DisplayBrightnessDriverTest, InitializeShouldSucceed)
{
    // Expect the clock enable function to be called once
    EXPECT_CALL(mockTimerInstance, __HAL_RCC_TIM3_CLK_ENABLE())
        .Times(1);

    // Expect the PWM initialization function to be called once
    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_Init(_))
        .WillOnce(Return(HAL_OK));

    // Expect the PWM channel configuration function to be called once
    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_ConfigChannel(_, _, _))
        .WillOnce(Return(HAL_OK));

    EXPECT_TRUE(driver->initialize());
    EXPECT_TRUE(driver->isInState(DriverState::State::Initialized));
}

TEST_F(St7735DisplayBrightnessDriverTest, StartShouldSucceed)
{
    // Ensure proper initialization is expected
    EXPECT_CALL(mockTimerInstance, __HAL_RCC_TIM3_CLK_ENABLE()).Times(AtLeast(1));
    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_Init(_)).WillOnce(Return(HAL_OK));
    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_ConfigChannel(_, _, _)).WillOnce(Return(HAL_OK));

    // This initializes the driver which includes the above calls
    ASSERT_TRUE(driver->initialize());

    // Expectations for the start process
    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_Start(_, _)).WillOnce(Return(HAL_OK));
    EXPECT_CALL(mockTimerInstance, __HAL_TIM_SET_COMPARE(_, _, _)).Times(AtLeast(1));

    // Execute the test
    EXPECT_TRUE(driver->start());
}

TEST_F(St7735DisplayBrightnessDriverTest, StopShouldSucceed)
{
    // Ensure it starts first
    EXPECT_CALL(mockTimerInstance, __HAL_RCC_TIM3_CLK_ENABLE()).Times(AtLeast(1));
    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_Init(_)).WillOnce(Return(HAL_OK));
    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_ConfigChannel(_, _, _)).WillOnce(Return(HAL_OK));

    ASSERT_TRUE(driver->initialize());

    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_Start(_, _)).WillOnce(Return(HAL_OK));
    EXPECT_CALL(mockTimerInstance, __HAL_TIM_SET_COMPARE(_, _, _)).Times(AtLeast(1));

    ASSERT_TRUE(driver->start());

    EXPECT_CALL(mockTimerInstance, HAL_TIM_PWM_Stop(_, _)).WillOnce(Return(HAL_OK));
    EXPECT_TRUE(driver->stop());

    EXPECT_TRUE(driver->isInState(DriverState::State::Stop));
    EXPECT_CALL(mockTimerInstance, __HAL_TIM_SET_COMPARE(_, _, _)).Times(0); // Expect no setting of compare value during stop
}

TEST_F(St7735DisplayBrightnessDriverTest, ResetShouldSucceed)
{
    EXPECT_TRUE(driver->reset());
    EXPECT_TRUE(driver->isInState(DriverState::State::Reset));
}

TEST_F(St7735DisplayBrightnessDriverTest, SetBrightnessWithinValidRange)
{
    const std::uint8_t validBrightness = 50;                            // Choose a valid brightness value within the range
    const std::uint32_t expectedPulse = (validBrightness * 4799) / 100; // Assuming the `calculatePulseFromBrightness` uses this formula

    // Expect the set compare function to be called with the calculated pulse
    EXPECT_CALL(mockTimerInstance, __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, expectedPulse))
        .Times(1)
        .WillOnce(Return());

    bool result = driver->setBrightness(validBrightness);
    EXPECT_TRUE(result);
}

TEST_F(St7735DisplayBrightnessDriverTest, SetBrightnessOutsideValidRange)
{
    const std::uint8_t invalidBrightness = 101; // Choose an invalid brightness value

    // The set compare function should not be called
    EXPECT_CALL(mockTimerInstance, __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, _))
        .Times(0);

    bool result = driver->setBrightness(invalidBrightness);
    EXPECT_FALSE(result);
}
