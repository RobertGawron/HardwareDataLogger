#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/UartStatus.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdint>
#include <cstring>
#include <span>

// --- Mocks ---

class MockUartDriver : public Driver::IUartDriver
{
public:
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
    MOCK_METHOD(Driver::UartStatus, transmit, (std::span<const std::uint8_t> data, std::uint32_t timeout), (override));
    MOCK_METHOD(Driver::UartStatus, receive, (std::span<std::uint8_t> data, std::uint32_t timeout), (override));
};

// --- Test Fixture ---

class WiFiMeasurementRecorderTest : public ::testing::Test
{
protected:
    // Test Constants
    static constexpr std::uint8_t TEST_MEASUREMENT_VALUE = 0x42U;

private:
    // Fields are now private
    MockUartDriver mockDriver;
    std::unique_ptr<Device::WiFiMeasurementRecorder> recorder;

protected:
    void SetUp() override
    {
        recorder = std::make_unique<Device::WiFiMeasurementRecorder>(mockDriver);
    }

public:
    // Public getters
    MockUartDriver &getMockDriver() { return mockDriver; }
    Device::WiFiMeasurementRecorder &getRecorder() { return *recorder; }
};

// --- Custom Matcher for span ---

MATCHER_P(SpanSizeIs, expectedSize, "")
{
    return arg.size() == expectedSize;
}

MATCHER(SpanNotEmpty, "")
{
    return !arg.empty();
}

// --- Test Cases ---

TEST_F(WiFiMeasurementRecorderTest, OnInitializeCallsDriverInitialize)
{
    EXPECT_CALL(getMockDriver(), onInitialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getRecorder().initialize());
}

TEST_F(WiFiMeasurementRecorderTest, OnInitializeFailsIfDriverInitializeFails)
{
    EXPECT_CALL(getMockDriver(), onInitialize()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(getRecorder().initialize());
}

TEST_F(WiFiMeasurementRecorderTest, OnStartCallsDriverStart)
{
    EXPECT_CALL(getMockDriver(), onInitialize()).WillOnce(::testing::Return(true));
    getRecorder().initialize();

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getRecorder().start());
}

TEST_F(WiFiMeasurementRecorderTest, OnStartFailsIfDriverStartFails)
{
    EXPECT_CALL(getMockDriver(), onInitialize()).WillOnce(::testing::Return(true));
    getRecorder().initialize();

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(getRecorder().start());
}

TEST_F(WiFiMeasurementRecorderTest, OnStopCallsDriverStop)
{
    EXPECT_CALL(getMockDriver(), onInitialize()).WillOnce(::testing::Return(true));
    getRecorder().initialize();

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(true));
    getRecorder().start();

    EXPECT_CALL(getMockDriver(), onStop()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getRecorder().stop());
}

TEST_F(WiFiMeasurementRecorderTest, OnStopFailsIfDriverStopFails)
{
    EXPECT_CALL(getMockDriver(), onInitialize()).WillOnce(::testing::Return(true));
    getRecorder().initialize();

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(true));
    getRecorder().start();

    EXPECT_CALL(getMockDriver(), onStop()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(getRecorder().stop());
}

TEST_F(WiFiMeasurementRecorderTest, OnResetReturnsTrue)
{
    EXPECT_CALL(getMockDriver(), onInitialize()).WillOnce(::testing::Return(true));
    getRecorder().initialize();

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(true));
    getRecorder().start();

    EXPECT_CALL(getMockDriver(), onReset()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(getRecorder().reset());
}

TEST_F(WiFiMeasurementRecorderTest, NotifySucceedsWhenTransmitOk)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(TEST_MEASUREMENT_VALUE);

    EXPECT_CALL(getMockDriver(), transmit(SpanNotEmpty(), ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(getRecorder().notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyFailsWhenTransmitFails)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(TEST_MEASUREMENT_VALUE);

    EXPECT_CALL(getMockDriver(), transmit(SpanNotEmpty(), ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Timeout));

    EXPECT_FALSE(getRecorder().notify(measurement));
}