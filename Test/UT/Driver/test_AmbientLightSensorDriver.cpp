#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Driver/Inc/AmbientLightSensorDriver.hpp"
#include "main.h"
#include "stm32f1xx_hal_adc.h"

using namespace testing;
using namespace Driver;

// Global pointer to the MockHAL instance
MockHAL *mockHAL = nullptr;

// Test fixture class for AmbientLightSensorDriver
class AmbientLightSensorDriverTest : public ::testing::Test
{
protected:
    ADC_HandleTypeDef hadc1{};
    AmbientLightSensorDriver driver{hadc1}; // Create an instance of the driver with the ADC handle
    MockHAL mockHALInstance;

    void SetUp() override
    {
        mockHAL = &mockHALInstance;
        //      memset(adcBuffer, 0, sizeof(adcBuffer)); // Clear the buffer
    }

    void TearDown() override
    {
        mockHAL = nullptr;
    }
};

TEST_F(AmbientLightSensorDriverTest, InitializeTransitionsToInitialized)
{
    // Expect no calls to HAL functions during initialization in this example
    EXPECT_TRUE(driver.initialize());
    EXPECT_EQ(driver.getState(), DriverState::State::Initialized);
}

TEST_F(AmbientLightSensorDriverTest, StartTransitionsToRunning)
{
    EXPECT_CALL(mockHALInstance, HAL_ADC_Start_DMA(_, _, _)).WillOnce(Return(HAL_OK));
    driver.initialize(); // Must be initialized before starting
    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), DriverState::State::Running);
}

TEST_F(AmbientLightSensorDriverTest, StopTransitionsToStopped)
{
    EXPECT_CALL(mockHALInstance, HAL_ADC_Stop_DMA(_)).WillOnce(Return(HAL_OK));
    driver.initialize();
    driver.start(); // Must be running before stopping
    EXPECT_TRUE(driver.stop());
    EXPECT_EQ(driver.getState(), DriverState::State::Stop);
}

TEST_F(AmbientLightSensorDriverTest, ResetTransitionsToReset)
{
    driver.initialize();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset());
    EXPECT_EQ(driver.getState(), DriverState::State::Reset);
}

TEST_F(AmbientLightSensorDriverTest, GetAmbientLightLevelAfterStart)
{
    // Simulate ADC buffer update by HAL
    const uint32_t simulatedLightLevel = 1234;
    EXPECT_CALL(mockHALInstance, HAL_ADC_Start_DMA(&hadc1, _, _))
        .WillOnce(DoAll(SetArrayArgument<1>(&simulatedLightLevel, &simulatedLightLevel + 1), Return(HAL_OK)));

    driver.initialize(); // This will call onInitialize which is mocked to do nothing here
    driver.start();      // This should trigger startAdcWithDma and modify the adcBuffer via HAL mock

    EXPECT_EQ(driver.getAmbientLightLevel(), simulatedLightLevel); // Check if the light level is as simulated
}
