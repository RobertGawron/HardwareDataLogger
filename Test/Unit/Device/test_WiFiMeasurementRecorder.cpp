#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"
#include "Driver/Inc/UartExchangeStatus.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>

// Mock for IUartDriver
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

class WiFiMeasurementRecorderTest : public ::testing::Test
{
protected:
    MockUartDriver mockDriver;
    Device::WiFiMeasurementRecorder *recorder;

    void SetUp() override
    {
        recorder = new Device::WiFiMeasurementRecorder(mockDriver);
    }

    void TearDown() override
    {
        delete recorder;
    }
};

// Test onInitialize()
TEST_F(WiFiMeasurementRecorderTest, OnInitializeCallsDriverInitialize)
{
    EXPECT_CALL(mockDriver, onInitialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->initialize());
}

TEST_F(WiFiMeasurementRecorderTest, OnInitializeFailsIfDriverInitializeFails)
{
    EXPECT_CALL(mockDriver, onInitialize()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(recorder->initialize());
}

// Test onStart()
TEST_F(WiFiMeasurementRecorderTest, OnStartCallsDriverStart)
{
    EXPECT_CALL(mockDriver, onInitialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->initialize());

    EXPECT_CALL(mockDriver, onStart()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->start());
}

TEST_F(WiFiMeasurementRecorderTest, OnStartFailsIfDriverStartFails)
{
    EXPECT_CALL(mockDriver, onInitialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->initialize());

    EXPECT_CALL(mockDriver, onStart()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(recorder->start());
}

// Test onStop()
TEST_F(WiFiMeasurementRecorderTest, OnStopCallsDriverStop)
{
    EXPECT_CALL(mockDriver, onInitialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->initialize());

    EXPECT_CALL(mockDriver, onStart()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->start());

    EXPECT_CALL(mockDriver, onStop()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->stop());
}

TEST_F(WiFiMeasurementRecorderTest, OnStopFailsIfDriverStopFails)
{
    EXPECT_CALL(mockDriver, onInitialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->initialize());

    EXPECT_CALL(mockDriver, onStart()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->start());

    EXPECT_CALL(mockDriver, onStop()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(recorder->stop());
}

TEST_F(WiFiMeasurementRecorderTest, OnResetReturnsTrue)
{
    EXPECT_CALL(mockDriver, onInitialize()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->initialize());

    EXPECT_CALL(mockDriver, onStart()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->start());

    EXPECT_CALL(mockDriver, onReset()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(recorder->reset());
}

TEST_F(WiFiMeasurementRecorderTest, NotifySucceedsWhenTransmitOk)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(0x42);

    EXPECT_CALL(mockDriver, transmit(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(Driver::UartExchangeStatus::Ok));

    EXPECT_TRUE(recorder->notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyFailsWhenTransmitFails)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(0x42);

    EXPECT_CALL(mockDriver, transmit(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(Driver::UartExchangeStatus::Timeout));

    EXPECT_FALSE(recorder->notify(measurement));
}
