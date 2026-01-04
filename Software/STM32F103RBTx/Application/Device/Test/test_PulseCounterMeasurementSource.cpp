#include "Device/Inc/PulseCounterSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "PulseCounterDriver.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// --- Mocks ---

class MockPulseCounterDriver : public Driver::PulseCounterDriver
{
public:
    MOCK_METHOD(Driver::PulseCounterMeasurementSize, getMeasurement, (), (override, noexcept));
    MOCK_METHOD(void, clearMeasurement, (), (override, noexcept));
    MOCK_METHOD(bool, onInit, (), (override, noexcept));
    MOCK_METHOD(bool, onStart, (), (override, noexcept));
    MOCK_METHOD(bool, onStop, (), (override, noexcept));
};

// --- Test Fixture ---

class PulseCounterSourceTest : public ::testing::Test
{
private:
    MockPulseCounterDriver mockDriver;
    std::unique_ptr<Device::PulseCounterSource> measurementSource;

protected:
    void SetUp() override
    {
        const Device::MeasurementDeviceId deviceId = Device::MeasurementDeviceId::PULSE_COUNTER_1;
        measurementSource = std::make_unique<Device::PulseCounterSource>(deviceId, mockDriver);
    }

public:
    MockPulseCounterDriver &getMockDriver() { return mockDriver; }
    Device::PulseCounterSource &getMeasurementSource() { return *measurementSource; }
};

// --- Test Cases ---

TEST_F(PulseCounterSourceTest, IsMeasurementAvailableReturnsTrue)
{
    EXPECT_TRUE(getMeasurementSource().isMeasurementAvailable());
}

TEST_F(PulseCounterSourceTest, GetMeasurementReturnsCorrectData)
{
    // Arrange
    constexpr Driver::PulseCounterMeasurementSize expectedCount = 42U;

    EXPECT_CALL(getMockDriver(), getMeasurement())
        .Times(1)
        .WillOnce(::testing::Return(expectedCount));

    // Act
    const auto measurement = getMeasurementSource().getMeasurement();

    // Assert
    EXPECT_EQ(measurement.source, Device::MeasurementDeviceId::PULSE_COUNTER_1);
    EXPECT_EQ(std::get<Driver::PulseCounterMeasurementSize>(measurement.data), expectedCount);
}