#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Driver/Interfaces/IPulseCounterDriver.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <array>
#include <variant>

constexpr Driver::PulseCounterIdentifier id = Driver::PulseCounterIdentifier::bncA;

// Mock class for IPulseCounterDriver
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

// Test Fixture for PULSE_COUNTER_MEASUREMENT_SOURCE
class PULSE_COUNTER_MEASUREMENT_SOURCE_TEST : public ::testing::Test
{
protected:
    MockPulseCounterDriver mockDriver;
    Device::PulseCounterMeasurementSource *measurementSource;

    void SetUp() override
    {
        Device::MeasurementDeviceId id = Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1;
        measurementSource = new Device::PulseCounterMeasurementSource(id, mockDriver);
    }

    void TearDown() override
    {
        delete measurementSource;
    }
};

// Test initialize() method
TEST_F(PULSE_COUNTER_MEASUREMENT_SOURCE_TEST, InitializeShouldCallDriverInitialize)
{
    EXPECT_CALL(mockDriver, onInitialize()).Times(1).WillOnce(::testing::Return(true));
    EXPECT_TRUE(measurementSource->initialize());
}

// Test start() method
TEST_F(PULSE_COUNTER_MEASUREMENT_SOURCE_TEST, StartShouldCallDriverStart)
{
    EXPECT_CALL(mockDriver, onInitialize()).Times(1).WillOnce(::testing::Return(true));
    EXPECT_TRUE(measurementSource->initialize());

    EXPECT_CALL(mockDriver, onStart()).Times(1).WillOnce(::testing::Return(true));
    EXPECT_TRUE(measurementSource->start());
}

