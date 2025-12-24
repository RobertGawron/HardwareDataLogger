#include "Driver/Hardware/Inc/AmbientLightSensorDriver.hpp"
#include "Driver/Interfaces/DriverState.hpp"

#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_def.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockHAL_ADC;

MockHAL_ADC *mockHAL_ADC = nullptr;

class AmbientLightSensorDriverTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        mockHAL_ADC = &mockHALInstance;
    }

    void TearDown() override
    {
        mockHAL_ADC = nullptr;
    }

    // Getters for accessing private members
    MockHAL_ADC &getMockHALInstance() { return mockHALInstance; }
    ADC_HandleTypeDef &getDummyADC() { return dummyADC; }

private:
    MockHAL_ADC mockHALInstance;
    ADC_HandleTypeDef dummyADC{};
};

TEST_F(AmbientLightSensorDriverTest, InitializeTransitionsToInitialized)
{
    Driver::AmbientLightSensorDriver driver(getDummyADC());

    // Expect no calls to HAL functions during initialization in this example
    EXPECT_TRUE(driver.initialize());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Initialized);
}

TEST_F(AmbientLightSensorDriverTest, StartTransitionsToRunning)
{
    Driver::AmbientLightSensorDriver driver(getDummyADC());

    EXPECT_CALL(getMockHALInstance(), HAL_ADC_Start_DMA(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));
    driver.initialize(); // Must be initialized before starting
    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Running);
}

TEST_F(AmbientLightSensorDriverTest, StopTransitionsToStopped)
{
    Driver::AmbientLightSensorDriver driver(getDummyADC());

    EXPECT_CALL(getMockHALInstance(), HAL_ADC_Stop_DMA(::testing::_))
        .WillOnce(::testing::Return(HAL_OK));
    driver.initialize();
    driver.start(); // Must be running before stopping
    EXPECT_TRUE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Stop);
}

TEST_F(AmbientLightSensorDriverTest, ResetTransitionsToReset)
{
    Driver::AmbientLightSensorDriver driver(getDummyADC());

    driver.initialize();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Reset);
}
