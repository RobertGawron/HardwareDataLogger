#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Driver/Inc/AmbientLightSensorDriver.hpp"
#include "stm32f1xx_hal_adc.h"

using namespace testing;

class MockHAL_ADC;

MockHAL_ADC *mockHAL_ADC = nullptr;

class AmbientLightSensorDriverTest : public ::testing::Test {
protected:
    MockHAL_ADC mockHALInstance;
    ADC_HandleTypeDef dummyADC {};

    void SetUp() override {
        mockHAL_ADC = &mockHALInstance;
    }

    void TearDown() override {
        mockHAL_ADC = nullptr;
    }
};

TEST_F(AmbientLightSensorDriverTest, InitializeTransitionsToInitialized)
{
    Driver::AmbientLightSensorDriver driver(dummyADC);

    // Expect no calls to HAL functions during initialization in this example
    EXPECT_TRUE(driver.initialize());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Initialized);
}

TEST_F(AmbientLightSensorDriverTest, StartTransitionsToRunning)
{
    Driver::AmbientLightSensorDriver driver(dummyADC);

    EXPECT_CALL(mockHALInstance, HAL_ADC_Start_DMA(_, _, _)).WillOnce(Return(HAL_OK));
    driver.initialize(); // Must be initialized before starting
    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Running);
}

TEST_F(AmbientLightSensorDriverTest, StopTransitionsToStopped)
{
    Driver::AmbientLightSensorDriver driver(dummyADC);

    EXPECT_CALL(mockHALInstance, HAL_ADC_Stop_DMA(_)).WillOnce(Return(HAL_OK));
    driver.initialize();
    driver.start(); // Must be running before stopping
    EXPECT_TRUE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Stop);
}

TEST_F(AmbientLightSensorDriverTest, ResetTransitionsToReset)
{
    Driver::AmbientLightSensorDriver driver(dummyADC);

    driver.initialize();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Reset);
}

TEST_F(AmbientLightSensorDriverTest, GetAmbientLightLevelAfterStart)
{
    /*
    // Simulate ADC buffer update by HAL
    const std::uint32_t simulatedLightLevel = 1234;
    EXPECT_CALL(mockHALInstance, HAL_ADC_Start_DMA(&hadc1, _, _))
        .WillOnce(DoAll(SetArrayArgument<1>(&simulatedLightLevel, &simulatedLightLevel + 1), Return(HAL_OK)));

    driver.initialize(); // This will call onInitialize which is mocked to do nothing here
    driver.start();      // This should trigger startAdcWithDma and modify the adcBuffer via HAL mock

    EXPECT_EQ(driver.getAmbientLightLevel(), simulatedLightLevel); // Check if the light level is as simulated
    */
}
