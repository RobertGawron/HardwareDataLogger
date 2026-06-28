#include "Driver/Hardware/Inc/LightSensorDriver.hpp"
#include "Driver/Interface/DriverComponent.hpp"

#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_def.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockHAL_ADC;

MockHAL_ADC *mockHAL_ADC = nullptr;

class LightSensorDriverTest : public ::testing::Test
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

TEST_F(LightSensorDriverTest, InitializeTransitionsToInitialized)
{
    Driver::LightSensorDriver driver(getDummyADC());

    // Expect no calls to HAL functions during initialization in this example
    EXPECT_TRUE(driver.init());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Initialized);
}

TEST_F(LightSensorDriverTest, StartTransitionsToRunning)
{
    Driver::LightSensorDriver driver(getDummyADC());

    EXPECT_CALL(getMockHALInstance(), HAL_ADC_Start_DMA(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(HAL_OK));
    driver.init(); // Must be initialized before starting
    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Running);
}

TEST_F(LightSensorDriverTest, StopTransitionsToStopped)
{
    Driver::LightSensorDriver driver(getDummyADC());

    EXPECT_CALL(getMockHALInstance(), HAL_ADC_Stop_DMA(::testing::_))
        .WillOnce(::testing::Return(HAL_OK));
    driver.init();
    driver.start(); // Must be running before stopping
    EXPECT_TRUE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Stop);
}

TEST_F(LightSensorDriverTest, ResetTransitionsToReset)
{
    Driver::LightSensorDriver driver(getDummyADC());

    driver.init();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::Reset);
}
