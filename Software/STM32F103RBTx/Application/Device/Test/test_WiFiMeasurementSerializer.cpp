#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/Crc32.hpp"

#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <span>
#include <expected>

// --- Test Fixture ---

class WiFiMeasurementSerializerTest : public ::testing::Test
{
protected:
    // Protocol Constants
    static constexpr std::size_t FIELD_LENGTH_SIZE = 2U;
    static constexpr std::size_t FIELD_SOURCE_SIZE = 1U;
    static constexpr std::size_t FIELD_CRC_SIZE = 4U;
    static constexpr std::size_t PROTOCOL_OVERHEAD = FIELD_LENGTH_SIZE + FIELD_SOURCE_SIZE + FIELD_CRC_SIZE;

    // Offset Constants
    static constexpr std::size_t OFFSET_LENGTH = 0U;
    static constexpr std::size_t OFFSET_SOURCE = FIELD_LENGTH_SIZE;
    static constexpr std::size_t OFFSET_DATA = FIELD_LENGTH_SIZE + FIELD_SOURCE_SIZE;

    // Bit manipulation constants
    static constexpr std::uint8_t BITS_PER_BYTE = 8U;
    static constexpr std::uint8_t SHIFT_BYTE_1 = 8U;
    static constexpr std::uint8_t SHIFT_BYTE_2 = 16U;
    static constexpr std::uint8_t SHIFT_BYTE_3 = 24U;
    static constexpr std::uint8_t BYTE_MASK = 0xFFU;

    // Size constants
    static constexpr std::size_t SIZE_WORD = 2U;
    static constexpr std::size_t SIZE_DWORD = 4U;

    // Buffer Configuration
    static constexpr std::size_t BUFFER_SIZE = 128U;

    // Test data constants
    static constexpr std::uint8_t TEST_DATA_BYTE = 0x42U;

    void SetUp() override
    {
        buffer.fill(0x00);
    }

    // Extract length field (Little Endian)
    [[nodiscard]] auto extractLength() const -> std::uint16_t
    {
        return std::uint16_t(buffer[OFFSET_LENGTH] | (buffer[OFFSET_LENGTH + 1U] << SHIFT_BYTE_1));
    }

    // Extract CRC field (Little Endian)
    [[nodiscard]] auto extractCRC(std::size_t offset) const -> std::uint32_t
    {
        return std::uint32_t(buffer[offset]) |
               (std::uint32_t(buffer[offset + 1U]) << SHIFT_BYTE_1) |
               (std::uint32_t(buffer[offset + 2U]) << SHIFT_BYTE_2) |
               (std::uint32_t(buffer[offset + 3U]) << SHIFT_BYTE_3);
    }

    // Extract Little Endian value
    template <typename T>
    [[nodiscard]] auto extractLittleEndian(std::size_t offset) const -> T
    {
        if constexpr (sizeof(T) == 1)
        {
            return static_cast<T>(buffer[offset]);
        }
        else if constexpr (sizeof(T) == SIZE_WORD)
        {
            std::uint16_t temp{};
            for (std::size_t i{}; i < sizeof(T); ++i)
            {
                temp |= std::uint16_t(buffer[offset + i]) << (i * BITS_PER_BYTE);
            }
            return static_cast<T>(temp);
        }
        else if constexpr (sizeof(T) == SIZE_DWORD)
        {
            std::uint32_t temp{};
            for (std::size_t i{}; i < sizeof(T); ++i)
            {
                temp |= std::uint32_t(buffer[offset + i]) << (i * BITS_PER_BYTE);
            }
            return static_cast<T>(temp);
        }
    }

    std::array<std::uint8_t, BUFFER_SIZE> buffer{};
};

// --- Test Cases ---

// Test 1: Serialize uint16_t
TEST_F(WiFiMeasurementSerializerTest, SerializesUint8Measurement)
{
    constexpr std::uint16_t TEST_VALUE = 0xABU;
    constexpr std::size_t EXPECTED_SIZE = PROTOCOL_OVERHEAD + sizeof(std::uint16_t);

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = TEST_VALUE};

    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, buffer);

    ASSERT_TRUE(result.has_value());
    const auto msgLength = result.value();
    EXPECT_EQ(msgLength, EXPECTED_SIZE);
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);
    EXPECT_EQ(buffer[OFFSET_SOURCE], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_1));
    EXPECT_EQ(buffer[OFFSET_DATA], static_cast<std::uint8_t>(TEST_VALUE & 0xFF));
    EXPECT_EQ(buffer[OFFSET_DATA + 1], static_cast<std::uint8_t>((TEST_VALUE >> 8) & 0xFF));
}

// Test 2: Serialize uint16_t (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, SerializesUint16Measurement)
{
    constexpr std::uint16_t TEST_VALUE = 0x1234U;
    constexpr std::size_t EXPECTED_SIZE = PROTOCOL_OVERHEAD + sizeof(std::uint16_t);

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_2,
        .data = TEST_VALUE};

    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, buffer);

    ASSERT_TRUE(result.has_value());
    const auto msgLength = result.value();
    EXPECT_EQ(msgLength, EXPECTED_SIZE);
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);
    EXPECT_EQ(buffer[OFFSET_SOURCE], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_2));
    EXPECT_EQ(buffer[OFFSET_DATA], 0x34U);      // LSB
    EXPECT_EQ(buffer[OFFSET_DATA + 1U], 0x12U); // MSB
    EXPECT_EQ(extractLittleEndian<std::uint16_t>(OFFSET_DATA), TEST_VALUE);
}

// Test 3: Serialize uint32_t (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, SerializesUint32Measurement)
{
    constexpr std::uint32_t TEST_VALUE = 0xAABBCCDDU;
    constexpr std::size_t EXPECTED_SIZE = PROTOCOL_OVERHEAD + sizeof(std::uint32_t);

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_3,
        .data = TEST_VALUE};

    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, buffer);

    ASSERT_TRUE(result.has_value());
    const auto msgLength = result.value();
    EXPECT_EQ(msgLength, EXPECTED_SIZE);
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);
    EXPECT_EQ(buffer[OFFSET_SOURCE], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_3));
    EXPECT_EQ(buffer[OFFSET_DATA], 0xDDU);      // Byte 0 (LSB)
    EXPECT_EQ(buffer[OFFSET_DATA + 1U], 0xCCU); // Byte 1
    EXPECT_EQ(buffer[OFFSET_DATA + 2U], 0xBBU); // Byte 2
    EXPECT_EQ(buffer[OFFSET_DATA + 3U], 0xAAU); // Byte 3 (MSB)
    EXPECT_EQ(extractLittleEndian<std::uint32_t>(OFFSET_DATA), TEST_VALUE);
}

// Test 4: Buffer too small
TEST_F(WiFiMeasurementSerializerTest, HandlesBufferTooSmall)
{
    constexpr std::size_t SMALL_BUFFER_SIZE = 3U;
    constexpr std::uint32_t TEST_VALUE = 0x12345678U;

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_3,
        .data = TEST_VALUE};

    std::array<std::uint8_t, SMALL_BUFFER_SIZE> smallBuffer{};
    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, smallBuffer);

    EXPECT_FALSE(result.has_value());
}

// Test 5: Zero-sized buffer
TEST_F(WiFiMeasurementSerializerTest, HandlesZeroBuffer)
{
    constexpr std::uint16_t TEST_VALUE = 0x42U;

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = TEST_VALUE};

    std::array<std::uint8_t, 0> zeroBuffer{};
    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, zeroBuffer);

    EXPECT_FALSE(result.has_value());
}

// Test 6: CRC Calculation Correctness (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, VerifiesCRCCalculation)
{
    constexpr std::uint16_t TEST_VALUE = 0xABCDU;

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_2,
        .data = TEST_VALUE};

    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, buffer);

    ASSERT_TRUE(result.has_value());
    const auto msgLength = result.value();

    const auto crcOffset = msgLength - FIELD_CRC_SIZE;
    const auto storedCRC = extractCRC(crcOffset);
    const auto dataSpan = std::span{buffer}.subspan(0, crcOffset);
    const auto calculatedCRC = Device::Crc32::compute(dataSpan);

    EXPECT_EQ(storedCRC, calculatedCRC);
    EXPECT_NE(storedCRC, 0U);
}

// Test 7: Zero value
TEST_F(WiFiMeasurementSerializerTest, SerializesZeroValue)
{
    constexpr std::uint32_t TEST_VALUE = 0U;

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_1,
        .data = TEST_VALUE};

    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, buffer);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(buffer[OFFSET_SOURCE], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_1));

    for (std::size_t i{}; i < sizeof(std::uint32_t); ++i)
    {
        EXPECT_EQ(buffer[OFFSET_DATA + i], 0x00U);
    }

    EXPECT_EQ(extractLittleEndian<std::uint32_t>(OFFSET_DATA), TEST_VALUE);
}

// Test 8: Maximum value
TEST_F(WiFiMeasurementSerializerTest, SerializesMaximumValue)
{
    constexpr std::uint32_t TEST_VALUE = 0xFFFFFFFFU;

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_3,
        .data = TEST_VALUE};

    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, buffer);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(buffer[OFFSET_SOURCE], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_3));

    for (std::size_t i{}; i < sizeof(std::uint32_t); ++i)
    {
        EXPECT_EQ(buffer[OFFSET_DATA + i], BYTE_MASK);
    }

    EXPECT_EQ(extractLittleEndian<std::uint32_t>(OFFSET_DATA), TEST_VALUE);
}

// Test 9: Verify Complete Protocol Format (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, VerifiesCompleteProtocolFormat)
{
    constexpr std::uint32_t TEST_VALUE = 0x12345678U;
    constexpr std::size_t EXPECTED_SIZE = PROTOCOL_OVERHEAD + sizeof(std::uint32_t);

    const auto measurement = Device::MeasurementType{
        .source = Device::MeasurementDeviceId::PULSE_COUNTER_4,
        .data = TEST_VALUE};

    const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, buffer);

    ASSERT_TRUE(result.has_value());
    const auto msgLength = result.value();
    EXPECT_EQ(msgLength, EXPECTED_SIZE);
    EXPECT_EQ(buffer[0], static_cast<std::uint8_t>(EXPECTED_SIZE & 0xFF));
    EXPECT_EQ(buffer[1], static_cast<std::uint8_t>((EXPECTED_SIZE >> 8) & 0xFF));
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);
    EXPECT_EQ(buffer[2], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_4));
    EXPECT_EQ(buffer[3], 0x78U); // LSB
    EXPECT_EQ(buffer[4], 0x56U);
    EXPECT_EQ(buffer[5], 0x34U);
    EXPECT_EQ(buffer[6], 0x12U); // MSB

    const auto crcOffset = msgLength - FIELD_CRC_SIZE;
    EXPECT_EQ(crcOffset, 7U);

    const auto storedCRC = extractCRC(crcOffset);
    const auto dataSpan = std::span{buffer}.subspan(0, crcOffset);
    const auto calculatedCRC = Device::Crc32::compute(dataSpan);
    EXPECT_EQ(storedCRC, calculatedCRC);
}

// Test 10: Different source IDs
TEST_F(WiFiMeasurementSerializerTest, HandlesAllSourceIds)
{
    constexpr std::array sourceIds{
        Device::MeasurementDeviceId::PULSE_COUNTER_1,
        Device::MeasurementDeviceId::PULSE_COUNTER_2,
        Device::MeasurementDeviceId::PULSE_COUNTER_3,
        Device::MeasurementDeviceId::PULSE_COUNTER_4,
        Device::MeasurementDeviceId::DEVICE_UART_1,
    };

    for (const auto sourceId : sourceIds)
    {
        const auto measurement = Device::MeasurementType{
            .source = sourceId,
            .data = std::uint16_t{TEST_DATA_BYTE}};

        std::array<std::uint8_t, BUFFER_SIZE> testBuffer{};
        const auto result = Device::WiFiMeasurementSerializer::serialize(measurement, testBuffer);

        ASSERT_TRUE(result.has_value()) << "Failed for source ID: " << static_cast<int>(sourceId);
        EXPECT_EQ(testBuffer[OFFSET_SOURCE], static_cast<std::uint8_t>(sourceId));
    }
}