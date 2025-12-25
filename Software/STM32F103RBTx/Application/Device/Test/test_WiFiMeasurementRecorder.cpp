#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/UartExchangeStatus.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdint>
#include <cstring>

// --- Mocks ---

class MockUartDriver : public Driver::IUartDriver
{
public:
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
    MOCK_METHOD(Driver::UartExchangeStatus, transmit, (std::uint8_t *data, std::uint16_t size, std::uint32_t timeout), (override));
    MOCK_METHOD(Driver::UartExchangeStatus, receive, (std::uint8_t *data, std::uint16_t size, std::uint32_t timeout), (override));
};

// --- Test Fixture ---

class WiFiMeasurementRecorderTest : public ::testing::Test
{
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
    measurement.source = Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(0x42);

    EXPECT_CALL(getMockDriver(), transmit(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(Driver::UartExchangeStatus::Ok));

    EXPECT_TRUE(getRecorder().notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyFailsWhenTransmitFails)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(0x42);

    EXPECT_CALL(getMockDriver(), transmit(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(Driver::UartExchangeStatus::Timeout));

    EXPECT_FALSE(getRecorder().notify(measurement));
}
