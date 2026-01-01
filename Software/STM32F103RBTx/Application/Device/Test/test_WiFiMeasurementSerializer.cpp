#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/Crc32.hpp"

#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <type_traits>

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

    // Size constants for type checking
    static constexpr std::size_t SIZE_BYTE = 1U;
    static constexpr std::size_t SIZE_WORD = 2U;
    static constexpr std::size_t SIZE_DWORD = 4U;
    static constexpr std::size_t SIZE_QWORD = 8U;

    // Buffer Configuration
    static constexpr std::size_t BUFFER_SIZE = 128U;

    // Test data constants
    static constexpr std::uint8_t TEST_DATA_BYTE = 0x42U;

    WiFiMeasurementSerializerTest() = default;

    void SetUp() override
    {
        buffer.fill(0x00);
        msgLength = 0U;
    }

    // Public getters for test access
    [[nodiscard]] const std::array<std::uint8_t, BUFFER_SIZE> &getBuffer() const { return buffer; }
    [[nodiscard]] std::array<std::uint8_t, BUFFER_SIZE> &getBuffer() { return buffer; }
    [[nodiscard]] std::size_t getMsgLength() const { return msgLength; }
    [[nodiscard]] std::size_t &getMsgLength() { return msgLength; }

    // Getters for constants
    [[nodiscard]] static constexpr std::size_t getProtocolOverhead() { return PROTOCOL_OVERHEAD; }
    [[nodiscard]] static constexpr std::size_t getOffsetSource() { return OFFSET_SOURCE; }
    [[nodiscard]] static constexpr std::size_t getOffsetData() { return OFFSET_DATA; }

    // Helper: Extract length field (Little Endian)
    [[nodiscard]] std::uint16_t extractLength() const
    {
        return static_cast<std::uint16_t>(
            buffer[OFFSET_LENGTH] |
            (buffer[OFFSET_LENGTH + 1U] << SHIFT_BYTE_1));
    }

    // Helper: Extract CRC field (Little Endian)
    [[nodiscard]] std::uint32_t extractCRC(std::size_t offset) const
    {
        return static_cast<std::uint32_t>(buffer[offset]) |
               (static_cast<std::uint32_t>(buffer[offset + 1U]) << SHIFT_BYTE_1) |
               (static_cast<std::uint32_t>(buffer[offset + 2U]) << SHIFT_BYTE_2) |
               (static_cast<std::uint32_t>(buffer[offset + 3U]) << SHIFT_BYTE_3);
    }

    // Helper: Extract Little Endian value
    template <typename T>
    [[nodiscard]] T extractLittleEndian(std::size_t offset) const
    {
        if constexpr (sizeof(T) == SIZE_BYTE)
        {
            return static_cast<T>(buffer[offset]);
        }
        else
        {
            using UIntType = std::conditional_t<sizeof(T) == SIZE_WORD, std::uint16_t,
                                                std::conditional_t<sizeof(T) == SIZE_DWORD, std::uint32_t,
                                                                   std::conditional_t<sizeof(T) == SIZE_QWORD, std::uint64_t, void>>>;
            UIntType temp = 0U;
            for (std::size_t i = 0U; i < sizeof(T); ++i)
            {
                temp |= static_cast<UIntType>(buffer[offset + i]) << (i * BITS_PER_BYTE);
            }
            T result;
            std::memcpy(&result, &temp, sizeof(T));
            return result;
        }
    }

    // Helper: Calculate CRC offset from message length
    [[nodiscard]] std::size_t getCRCOffset() const
    {
        return msgLength - FIELD_CRC_SIZE;
    }

private:
    std::array<std::uint8_t, BUFFER_SIZE> buffer{};
    std::size_t msgLength{0U};
};

// --- Test Cases ---

// Test 1: Serialize uint8_t
TEST_F(WiFiMeasurementSerializerTest, SerializesUint8Measurement)
{
    constexpr std::uint8_t TEST_VALUE = 0xABU;
    const std::size_t EXPECTED_SIZE = getProtocolOverhead() + sizeof(std::uint8_t);

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getBuffer(), getMsgLength());

    ASSERT_TRUE(status);
    EXPECT_EQ(getMsgLength(), EXPECTED_SIZE);

    // Verify Length field (Little Endian)
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);

    // Verify Source field
    EXPECT_EQ(getBuffer()[getOffsetSource()], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_1));

    // Verify Data field
    EXPECT_EQ(getBuffer()[getOffsetData()], TEST_VALUE);
}

// Test 2: Serialize uint16_t (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, SerializesUint16Measurement)
{
    constexpr std::uint16_t TEST_VALUE = 0x1234U;
    const std::size_t EXPECTED_SIZE = getProtocolOverhead() + sizeof(std::uint16_t);

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_2;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getBuffer(), getMsgLength());

    ASSERT_TRUE(status);
    EXPECT_EQ(getMsgLength(), EXPECTED_SIZE);
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);
    EXPECT_EQ(getBuffer()[getOffsetSource()], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_2));

    // Check Little Endian serialization (LSB first)
    EXPECT_EQ(getBuffer()[getOffsetData()], 0x34U);      // LSB
    EXPECT_EQ(getBuffer()[getOffsetData() + 1U], 0x12U); // MSB

    // Verify extracted value
    const std::uint16_t extracted = extractLittleEndian<std::uint16_t>(getOffsetData());
    EXPECT_EQ(extracted, TEST_VALUE);
}

// Test 3: Serialize uint32_t (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, SerializesUint32Measurement)
{
    constexpr std::uint32_t TEST_VALUE = 0xAABBCCDDU;
    const std::size_t EXPECTED_SIZE = getProtocolOverhead() + sizeof(std::uint32_t);

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_3;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getBuffer(), getMsgLength());

    ASSERT_TRUE(status);
    EXPECT_EQ(getMsgLength(), EXPECTED_SIZE);
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);
    EXPECT_EQ(getBuffer()[getOffsetSource()], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_3));

    // Check Little Endian serialization (LSB first)
    EXPECT_EQ(getBuffer()[getOffsetData()], 0xDDU);      // Byte 0 (LSB)
    EXPECT_EQ(getBuffer()[getOffsetData() + 1U], 0xCCU); // Byte 1
    EXPECT_EQ(getBuffer()[getOffsetData() + 2U], 0xBBU); // Byte 2
    EXPECT_EQ(getBuffer()[getOffsetData() + 3U], 0xAAU); // Byte 3 (MSB)

    // Verify extracted value
    const std::uint32_t extracted = extractLittleEndian<std::uint32_t>(getOffsetData());
    EXPECT_EQ(extracted, TEST_VALUE);
}

// Test 4: Buffer too small
TEST_F(WiFiMeasurementSerializerTest, HandlesBufferTooSmall)
{
    constexpr std::size_t SMALL_BUFFER_SIZE = 3U;
    constexpr std::uint32_t TEST_VALUE = 0x12345678U;

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_3;

    std::array<std::uint8_t, SMALL_BUFFER_SIZE> smallBuffer{};
    std::size_t length = 0U;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, smallBuffer, length);

    EXPECT_FALSE(status);
    EXPECT_EQ(length, 0U);
}

// Test 5: Zero-sized buffer
TEST_F(WiFiMeasurementSerializerTest, HandlesZeroBuffer)
{
    constexpr std::size_t ZERO_BUFFER_SIZE = 0U;
    constexpr std::uint8_t TEST_VALUE = 0x42U;

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;

    std::array<std::uint8_t, ZERO_BUFFER_SIZE> zeroBuffer{};
    std::size_t length = 0U;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, zeroBuffer, length);

    EXPECT_FALSE(status);
    EXPECT_EQ(length, 0U);
}

// Test 6: CRC Calculation Correctness (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, VerifiesCRCCalculation)
{
    constexpr std::uint16_t TEST_VALUE = 0xABCDU;

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_2;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getBuffer(), getMsgLength());

    ASSERT_TRUE(status);

    // CRC should be calculated over [Length + Source + Data]
    const std::size_t crcOffset = getCRCOffset();
    const std::uint32_t storedCRC = extractCRC(crcOffset);

    // Recalculate CRC
    const std::uint32_t calculatedCRC = Device::Crc32::compute(getBuffer(), crcOffset);

    EXPECT_EQ(storedCRC, calculatedCRC);
    EXPECT_NE(storedCRC, 0U); // CRC should not be zero for this data
}

// Test 7: Zero value
TEST_F(WiFiMeasurementSerializerTest, SerializesZeroValue)
{
    constexpr std::uint32_t TEST_VALUE = 0U;

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_1;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getBuffer(), getMsgLength());

    ASSERT_TRUE(status);
    EXPECT_EQ(getBuffer()[getOffsetSource()], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_1));

    // Verify all data bytes are zero
    for (std::size_t i = 0U; i < sizeof(std::uint32_t); ++i)
    {
        EXPECT_EQ(getBuffer()[getOffsetData() + i], 0x00U);
    }

    // Verify extracted value
    const std::uint32_t extracted = extractLittleEndian<std::uint32_t>(getOffsetData());
    EXPECT_EQ(extracted, TEST_VALUE);
}

// Test 8: Maximum value
TEST_F(WiFiMeasurementSerializerTest, SerializesMaximumValue)
{
    constexpr std::uint32_t TEST_VALUE = 0xFFFFFFFFU;

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_3;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getBuffer(), getMsgLength());

    ASSERT_TRUE(status);
    EXPECT_EQ(getBuffer()[getOffsetSource()], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_3));

    // Verify all data bytes are 0xFF
    for (std::size_t i = 0U; i < sizeof(std::uint32_t); ++i)
    {
        EXPECT_EQ(getBuffer()[getOffsetData() + i], BYTE_MASK);
    }

    // Verify extracted value
    const std::uint32_t extracted = extractLittleEndian<std::uint32_t>(getOffsetData());
    EXPECT_EQ(extracted, TEST_VALUE);
}

// Test 9: Verify Complete Protocol Format (Little Endian)
TEST_F(WiFiMeasurementSerializerTest, VerifiesCompleteProtocolFormat)
{
    constexpr std::uint32_t TEST_VALUE = 0x12345678U;
    const std::size_t EXPECTED_SIZE = getProtocolOverhead() + sizeof(std::uint32_t);

    Device::MeasurementType measurement;
    measurement.data = TEST_VALUE;
    measurement.source = Device::MeasurementDeviceId::PULSE_COUNTER_4;

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getBuffer(), getMsgLength());

    ASSERT_TRUE(status);
    EXPECT_EQ(getMsgLength(), EXPECTED_SIZE);

    // Verify Length field (Little Endian)
    EXPECT_EQ(getBuffer()[0], static_cast<std::uint8_t>(EXPECTED_SIZE & 0xFF));        // LSB
    EXPECT_EQ(getBuffer()[1], static_cast<std::uint8_t>((EXPECTED_SIZE >> 8) & 0xFF)); // MSB
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);

    // Verify Source field
    EXPECT_EQ(getBuffer()[2], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_4));

    // Verify Data field (Little Endian: 78 56 34 12)
    EXPECT_EQ(getBuffer()[3], 0x78U); // LSB
    EXPECT_EQ(getBuffer()[4], 0x56U);
    EXPECT_EQ(getBuffer()[5], 0x34U);
    EXPECT_EQ(getBuffer()[6], 0x12U); // MSB

    // Verify CRC is present and in Little Endian format
    const std::size_t crcOffset = getCRCOffset();
    EXPECT_EQ(crcOffset, 7U); // Length(2) + Source(1) + Data(4) = 7

    // CRC should be stored in Little Endian
    const std::uint32_t storedCRC = extractCRC(crcOffset);
    const std::uint32_t calculatedCRC = Device::Crc32::compute(getBuffer(), crcOffset);
    EXPECT_EQ(storedCRC, calculatedCRC);
}

// Test 10: Different source IDs
TEST_F(WiFiMeasurementSerializerTest, HandlesAllSourceIds)
{
    const std::array<Device::MeasurementDeviceId, 5> sourceIds = {
        Device::MeasurementDeviceId::PULSE_COUNTER_1,
        Device::MeasurementDeviceId::PULSE_COUNTER_2,
        Device::MeasurementDeviceId::PULSE_COUNTER_3,
        Device::MeasurementDeviceId::PULSE_COUNTER_4,
        Device::MeasurementDeviceId::DEVICE_UART_1,
    };

    for (const auto sourceId : sourceIds)
    {
        Device::MeasurementType measurement;
        measurement.data = static_cast<std::uint8_t>(TEST_DATA_BYTE);
        measurement.source = sourceId;

        std::array<std::uint8_t, BUFFER_SIZE> testBuffer{};
        std::size_t testLength = 0U;

        const bool status = Device::WiFiMeasurementSerializer::generate(measurement, testBuffer, testLength);

        ASSERT_TRUE(status) << "Failed for source ID: " << static_cast<int>(sourceId);
        EXPECT_EQ(testBuffer[OFFSET_SOURCE], static_cast<std::uint8_t>(sourceId));
    }
}
