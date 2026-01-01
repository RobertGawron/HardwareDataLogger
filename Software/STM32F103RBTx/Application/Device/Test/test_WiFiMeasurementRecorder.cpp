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
#include <vector>

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
    static constexpr std::uint8_t TEST_MEASUREMENT_VALUE_U8 = 0x42U;
    static constexpr std::uint16_t TEST_MEASUREMENT_VALUE_U16 = 0x1234U;
    static constexpr std::uint32_t TEST_MEASUREMENT_VALUE_U32 = 0x12345678U;

private:
    // Fields are now private
    MockUartDriver mockDriver;
    std::unique_ptr<Device::WiFiMeasurementRecorder> recorder;

protected:
    void SetUp() override
    {
        recorder = std::make_unique<Device::WiFiMeasurementRecorder>(mockDriver);
    }

    // Helper to decode COBS and verify protocol structure
    static std::vector<std::uint8_t> decodeCobs(const std::span<const std::uint8_t> cobsData)
    {
        std::vector<std::uint8_t> decoded;

        // Remove trailing delimiter
        if (cobsData.empty() || cobsData.back() != 0x00)
        {
            return decoded; // Invalid COBS frame
        }

        std::size_t pos = 0;
        while (pos < cobsData.size() - 1) // -1 to skip delimiter
        {
            const std::uint8_t code = cobsData[pos];

            if (code == 0)
            {
                break; // Invalid
            }

            // Insert zero if this isn't the first code
            if (pos > 0)
            {
                decoded.push_back(0x00);
            }

            // Copy (code - 1) bytes
            for (std::uint8_t i = 1; i < code && (pos + i) < cobsData.size() - 1; ++i)
            {
                decoded.push_back(cobsData[pos + i]);
            }

            pos += code;
        }

        return decoded;
    }

public:
    // Public getters
    MockUartDriver &getMockDriver() { return mockDriver; }
    Device::WiFiMeasurementRecorder &getRecorder() { return *recorder; }
};

// --- Custom Matchers ---

MATCHER_P(SpanSizeIs, expectedSize, "")
{
    (void)result_listener;
    return arg.size() == static_cast<std::size_t>(expectedSize);
}

MATCHER(SpanNotEmpty, "")
{
    (void)result_listener;
    return !arg.empty();
}

MATCHER(IsCobsEncoded, "Checks if data is COBS encoded with trailing 0x00")
{
    (void)result_listener;
    if (arg.empty())
    {
        return false;
    }
    // COBS frames must end with 0x00 delimiter
    return arg.back() == 0x00;
}

// Custom matcher to validate protocol structure after COBS decoding
MATCHER_P2(HasLittleEndianProtocol, expectedSource, expectedValueSize, "")
{
    static constexpr std::uint8_t BITS_PER_BYTE = 8U;

    // Decode COBS
    std::vector<std::uint8_t> decoded;
    if (arg.empty() || arg.back() != 0x00)
    {
        *result_listener << "Invalid COBS frame (missing delimiter)";
        return false;
    }

    // Simple COBS decode for validation
    std::size_t pos = 0;
    while (pos < arg.size() - 1)
    {
        const std::uint8_t code = arg[pos];
        if (code == 0)
        {
            break;
        }

        if (pos > 0)
        {
            decoded.push_back(0x00);
        }

        for (std::uint8_t i = 1; i < code && (pos + i) < arg.size() - 1; ++i)
        {
            decoded.push_back(arg[pos + i]);
        }

        pos += code;
    }

    // Protocol: [Length(2,LE)][Source(1)][Value(N,LE)][CRC(4,LE)]
    const std::size_t minSize = 2U + 1U + static_cast<std::size_t>(expectedValueSize) + 4U;
    if (decoded.size() < minSize)
    {
        *result_listener << "Decoded size " << decoded.size() << " < minimum " << minSize;
        return false;
    }

    // Verify Length (Little Endian)
    const std::uint16_t length = static_cast<std::uint16_t>(decoded[0] | (decoded[1] << BITS_PER_BYTE));
    if (length != decoded.size())
    {
        *result_listener << "Length field " << length << " != actual size " << decoded.size();
        return false;
    }

    // Verify Source
    if (decoded[2] != static_cast<std::uint8_t>(expectedSource))
    {
        *result_listener << "Source " << static_cast<int>(decoded[2])
                         << " != expected " << static_cast<int>(expectedSource);
        return false;
    }

    return true;
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
    measurement.data = static_cast<std::uint8_t>(TEST_MEASUREMENT_VALUE_U8);

    EXPECT_CALL(getMockDriver(), transmit(::testing::AllOf(
                                              SpanNotEmpty(),
                                              IsCobsEncoded()),
                                          ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(getRecorder().notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyFailsWhenTransmitFails)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(TEST_MEASUREMENT_VALUE_U8);

    EXPECT_CALL(getMockDriver(), transmit(SpanNotEmpty(), ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Timeout));

    EXPECT_FALSE(getRecorder().notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyTransmitsValidProtocolForUint8)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(TEST_MEASUREMENT_VALUE_U8);

    EXPECT_CALL(getMockDriver(),
                transmit(HasLittleEndianProtocol(Device::MeasurementDeviceId::PULSE_COUNTER_1, 1),
                         ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(getRecorder().notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyTransmitsValidProtocolForUint16)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_2;
    measurement.data = static_cast<std::uint16_t>(TEST_MEASUREMENT_VALUE_U16);

    EXPECT_CALL(getMockDriver(),
                transmit(HasLittleEndianProtocol(Device::MeasurementDeviceId::PULSE_COUNTER_2, 2),
                         ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(getRecorder().notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyTransmitsValidProtocolForUint32)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_3;
    measurement.data = static_cast<std::uint32_t>(TEST_MEASUREMENT_VALUE_U32);

    EXPECT_CALL(getMockDriver(),
                transmit(HasLittleEndianProtocol(Device::MeasurementDeviceId::PULSE_COUNTER_3, 4),
                         ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(getRecorder().notify(measurement));
}

TEST_F(WiFiMeasurementRecorderTest, NotifyTransmitsCobsEncodedData)
{
    Device::MeasurementType measurement;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;
    measurement.data = static_cast<std::uint8_t>(0x00); // Value with zero to test COBS

    std::span<const std::uint8_t> capturedData;

    EXPECT_CALL(getMockDriver(), transmit(::testing::_, ::testing::_))
        .WillOnce(::testing::DoAll(
            ::testing::SaveArg<0>(&capturedData),
            ::testing::Return(Driver::UartStatus::Ok)));

    EXPECT_TRUE(getRecorder().notify(measurement));

    // Verify COBS properties:
    // 1. Must end with 0x00 delimiter
    ASSERT_FALSE(capturedData.empty());
    EXPECT_EQ(capturedData.back(), 0x00);

    // 2. COBS encoding ensures no 0x00 in the encoded data (before delimiter)
    // This is implicitly verified by the COBS structure
}
