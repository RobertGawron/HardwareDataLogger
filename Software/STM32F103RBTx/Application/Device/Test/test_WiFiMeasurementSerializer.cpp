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

    // Constructor to initialize members
    WiFiMeasurementSerializerTest() {}

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

    // Helper: Extract length field (Big Endian)
    [[nodiscard]] std::uint16_t extractLength() const
    {
        return static_cast<std::uint16_t>(
            (buffer[OFFSET_LENGTH] << SHIFT_BYTE_1) |
            buffer[OFFSET_LENGTH + 1U]);
    }

    // Helper: Extract CRC field (Big Endian)
    [[nodiscard]] std::uint32_t extractCRC(std::size_t offset) const
    {
        return (static_cast<std::uint32_t>(buffer[offset]) << SHIFT_BYTE_3) |
               (static_cast<std::uint32_t>(buffer[offset + 1U]) << SHIFT_BYTE_2) |
               (static_cast<std::uint32_t>(buffer[offset + 2U]) << SHIFT_BYTE_1) |
               static_cast<std::uint32_t>(buffer[offset + 3U]);
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
    std::size_t msgLength{0u};
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
    EXPECT_EQ(extractLength(), EXPECTED_SIZE);
    EXPECT_EQ(getBuffer()[getOffsetSource()], static_cast<std::uint8_t>(Device::MeasurementDeviceId::PULSE_COUNTER_1));
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
    EXPECT_EQ(getBuffer()[getOffsetData()], static_cast<std::uint8_t>(TEST_VALUE & BYTE_MASK));                        // 0x34
    EXPECT_EQ(getBuffer()[getOffsetData() + 1U], static_cast<std::uint8_t>((TEST_VALUE >> SHIFT_BYTE_1) & BYTE_MASK)); // 0x12

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
    EXPECT_EQ(getBuffer()[getOffsetData()], static_cast<std::uint8_t>(TEST_VALUE & BYTE_MASK));                        // 0xDD
    EXPECT_EQ(getBuffer()[getOffsetData() + 1U], static_cast<std::uint8_t>((TEST_VALUE >> SHIFT_BYTE_1) & BYTE_MASK)); // 0xCC
    EXPECT_EQ(getBuffer()[getOffsetData() + 2U], static_cast<std::uint8_t>((TEST_VALUE >> SHIFT_BYTE_2) & BYTE_MASK)); // 0xBB
    EXPECT_EQ(getBuffer()[getOffsetData() + 3U], static_cast<std::uint8_t>((TEST_VALUE >> SHIFT_BYTE_3) & BYTE_MASK)); // 0xAA

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

// Test 6: CRC Calculation Correctness
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
