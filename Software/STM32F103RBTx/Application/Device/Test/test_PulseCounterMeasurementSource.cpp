#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// --- Mocks ---

class MockPulseCounterDriver : public Driver::IPulseCounterDriver
{
public:
    MOCK_METHOD(Driver::IPulseCounterDriver::CounterSizeType, getMeasurement, (), (override));
    MOCK_METHOD(void, clearMeasurement, (), (override));
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
};

// --- Test Fixture ---

class PulseCounterMeasurementSourceTest : public ::testing::Test
{
private:
    // All fields are now private
    MockPulseCounterDriver mockDriver;
    std::unique_ptr<Device::PulseCounterMeasurementSource> measurementSource;

protected:
    void SetUp() override
    {
        const Device::MeasurementDeviceId deviceId = Device::MeasurementDeviceId::PULSE_COUNTER_1;
        measurementSource = std::make_unique<Device::PulseCounterMeasurementSource>(deviceId, mockDriver);
    }

public:
    // Public getters to access private members
    MockPulseCounterDriver &getMockDriver() { return mockDriver; }
    Device::PulseCounterMeasurementSource &getMeasurementSource() { return *measurementSource; }
};

// --- Test Cases ---

TEST_F(PulseCounterMeasurementSourceTest, InitializeShouldCallDriverInitialize)
{
    // Arrange & Assert
    EXPECT_CALL(getMockDriver(), onInitialize())
        .Times(1)
        .WillOnce(::testing::Return(true));

    // Act
    EXPECT_TRUE(getMeasurementSource().initialize());
}

TEST_F(PulseCounterMeasurementSourceTest, StartShouldCallDriverStart)
{
    // Arrange: Initialization must happen first
    EXPECT_CALL(getMockDriver(), onInitialize())
        .Times(1)
        .WillOnce(::testing::Return(true));

    getMeasurementSource().initialize();

    // Assert: Expect start call
    EXPECT_CALL(getMockDriver(), onStart())
        .Times(1)
        .WillOnce(::testing::Return(true));

    // Act
    EXPECT_TRUE(getMeasurementSource().start());
}
