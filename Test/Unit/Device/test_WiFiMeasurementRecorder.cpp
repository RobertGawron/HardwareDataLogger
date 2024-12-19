#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"
#include "Driver/Inc/UartExchangeStatus.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring> // For memcmp

// Mock class for IUartDriver
class MockUartDriver : public Driver::IUartDriver
{
public:
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
    MOCK_METHOD(Driver::UartExchangeStatus, transmit, (std::uint8_t * data, std::uint16_t size, std::uint32_t timeout), (override));
    MOCK_METHOD(Driver::UartExchangeStatus, receive, (std::uint8_t * data, std::uint16_t size, std::uint32_t timeout), (override));
};

// Test Fixture for WiFiMeasurementRecorder
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
/*
// Test notify() calls write()
TEST_F(WiFiMeasurementRecorderTest, NotifyCallsWrite)
{
    // TOD rework this test
    //    Device::MeasurementType inputData{42u}; // The expected measurement value
    std::uint8_t data = 5;
    Device::MeasurementType d(data);
    // Using EXPECT_CALL to capture the behavior within write()
    std::uint8_t expectedData[] = {data, '\r', '\n'};

    EXPECT_CALL(mockDriver, transmit(::testing::_, sizeof(expectedData), Driver::IUartDriver::MaxDelay))
        .WillOnce([&](std::uint8_t *data, std::uint16_t size, std::uint32_t)
                  {
            EXPECT_EQ(size, sizeof(expectedData));
            EXPECT_EQ(std::memcmp(data, expectedData, size), 0) << "Transmitted data does not match expected content";
            return Driver::UartExchangeStatus::Ok; });

    recorder->notify(d);
}*/
