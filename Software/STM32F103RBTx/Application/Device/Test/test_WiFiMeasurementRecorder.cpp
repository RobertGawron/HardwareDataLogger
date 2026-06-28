#include "Device/Inc/WiFiRecorder.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "UartDriver.hpp"
#include "Driver/Interface/UartStatus.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdint>
#include <span>
#include <vector>

// --- Mocks ---

class MockUartDriver : public Driver::UartDriver
{
public:
    MOCK_METHOD(bool, onInit, (), (override, noexcept));
    MOCK_METHOD(bool, onStart, (), (override, noexcept));
    MOCK_METHOD(bool, onStop, (), (override, noexcept));
    MOCK_METHOD(Driver::UartStatus, transmit, (std::span<const std::uint8_t> data, std::uint32_t timeout), (override));
    MOCK_METHOD(Driver::UartStatus, receive, (std::span<std::uint8_t> data, std::uint32_t timeout), (override));
};

// --- Test Fixture ---

class WiFiRecorderTest : public ::testing::Test
{
protected:
    static constexpr std::uint16_t TEST_MEASUREMENT_VALUE_U16 = 0x1234U;
    static constexpr std::uint32_t TEST_MEASUREMENT_VALUE_U32 = 0x12345678U;

    MockUartDriver mockDriver;
    std::unique_ptr<Device::WiFiRecorder> recorder;

    void SetUp() override
    {
        recorder = std::make_unique<Device::WiFiRecorder>(mockDriver);
    }

    void TearDown() override
    {
        recorder.reset();
    }
};

// --- Custom Matchers ---

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
    return arg.back() == 0x00;
}

// Custom matcher to validate protocol structure after COBS decoding
MATCHER_P2(HasLittleEndianProtocol, expectedSource, expectedValueSize, "")
{
    static constexpr std::uint8_t BITS_PER_BYTE = 8U;

    std::vector<std::uint8_t> decoded;
    if (arg.empty() || arg.back() != 0x00)
    {
        *result_listener << "Invalid COBS frame (missing delimiter)";
        return false;
    }

    // Simple COBS decode for validation
    std::size_t pos{};
    while (pos < arg.size() - 1)
    {
        const auto code = arg[pos];
        if (code == 0)
        {
            break;
        }

        if (pos > 0)
        {
            decoded.push_back(0x00);
        }

        for (std::uint8_t i{1}; i < code && (pos + i) < arg.size() - 1; ++i)
        {
            decoded.push_back(arg[pos + i]);
        }

        pos += code;
    }

    // Protocol: [Length(2,LE)][Source(1)][Value(N,LE)][CRC(4,LE)]
    const auto minSize = 2U + 1U + static_cast<std::size_t>(expectedValueSize) + 4U;
    if (decoded.size() < minSize)
    {
        *result_listener << "Decoded size " << decoded.size() << " < minimum " << minSize;
        return false;
    }

    // Verify Length (Little Endian)
    const auto length = std::uint16_t(decoded[0] | (decoded[1] << BITS_PER_BYTE));
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

TEST_F(WiFiRecorderTest, NotifySucceedsWhenTransmitOk)
{
    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = TEST_MEASUREMENT_VALUE_U16};

    EXPECT_CALL(mockDriver, transmit(::testing::AllOf(
                                         SpanNotEmpty(),
                                         IsCobsEncoded()),
                                     ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(recorder->notify(measurement));
}

TEST_F(WiFiRecorderTest, NotifyFailsWhenTransmitFails)
{
    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = TEST_MEASUREMENT_VALUE_U16};

    EXPECT_CALL(mockDriver, transmit(SpanNotEmpty(), ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Timeout));

    EXPECT_FALSE(recorder->notify(measurement));
}

TEST_F(WiFiRecorderTest, NotifyTransmitsValidProtocolForUint16)
{
    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_2,
        .data = TEST_MEASUREMENT_VALUE_U16};

    EXPECT_CALL(mockDriver,
                transmit(HasLittleEndianProtocol(Device::MeasurementDeviceId::PULSE_COUNTER_2, 2),
                         ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(recorder->notify(measurement));
}

TEST_F(WiFiRecorderTest, NotifyTransmitsValidProtocolForUint32)
{
    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_3,
        .data = TEST_MEASUREMENT_VALUE_U32};

    EXPECT_CALL(mockDriver,
                transmit(HasLittleEndianProtocol(Device::MeasurementDeviceId::PULSE_COUNTER_3, 4),
                         ::testing::_))
        .WillOnce(::testing::Return(Driver::UartStatus::Ok));

    EXPECT_TRUE(recorder->notify(measurement));
}

TEST_F(WiFiRecorderTest, NotifyTransmitsCobsEncodedDataWithZeroBytes)
{
    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = std::uint16_t{0x0000} // Value with zeros to test COBS encoding
    };

    std::span<const std::uint8_t> capturedData;

    EXPECT_CALL(mockDriver, transmit(::testing::_, ::testing::_))
        .WillOnce(::testing::DoAll(
            ::testing::SaveArg<0>(&capturedData),
            ::testing::Return(Driver::UartStatus::Ok)));

    EXPECT_TRUE(recorder->notify(measurement));

    // Verify COBS properties: must end with 0x00 delimiter
    ASSERT_FALSE(capturedData.empty());
    EXPECT_EQ(capturedData.back(), 0x00);

    // Verify no zero bytes in the encoded data (except delimiter)
    for (std::size_t i = 0; i < capturedData.size() - 1; ++i)
    {
        EXPECT_NE(capturedData[i], 0x00) << "Found zero byte at position " << i;
    }
}