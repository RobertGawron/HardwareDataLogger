#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <cstddef>
#include <variant>

// --- Test Fixture ---

class WiFiMeasurementSerializerTest : public ::testing::Test
{
private:
    static constexpr std::size_t BUFFER_SIZE = 128U;
    std::array<std::uint8_t, BUFFER_SIZE> dataBuffer = {0};

public:
    // Return the array by reference so the template can deduce the size
    std::array<std::uint8_t, BUFFER_SIZE> &getDataBuffer() { return dataBuffer; }

    // Getter for specific index access
    std::uint8_t getBufferAt(std::size_t index) const { return dataBuffer.at(index); }

protected:
    Device::MeasurementType createMeasurement(Device::MeasurementDeviceId id,
                                              std::variant<std::uint8_t, std::uint16_t, std::uint32_t> value)
    {
        Device::MeasurementType measurement;
        measurement.source = id;
        measurement.data = value;
        return measurement;
    }
};

// --- Test Cases ---

TEST_F(WiFiMeasurementSerializerTest, SerializesUint8Measurement)
{
    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1,
        static_cast<std::uint8_t>(0xAB));

    std::size_t msgLength = 0;
    // Pass the array reference directly. Template deduces BUFFER_SIZE.
    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getDataBuffer(), msgLength);

    static constexpr std::size_t EXPECTED_LENGTH = 2U + 1U + 1U + 4U; // Header + ID + Data + CRC

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, EXPECTED_LENGTH);
    EXPECT_EQ(getBufferAt(2), static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1));
    EXPECT_EQ(getBufferAt(3), 0xAB);
}

TEST_F(WiFiMeasurementSerializerTest, SerializesUint16Measurement)
{
    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2,
        static_cast<std::uint16_t>(0x1234));

    std::size_t msgLength = 0;
    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getDataBuffer(), msgLength);

    static constexpr std::size_t EXPECTED_LENGTH = 2U + 1U + 2U + 4U;

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, EXPECTED_LENGTH);
    EXPECT_EQ(getBufferAt(2), static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2));
    EXPECT_EQ(getBufferAt(3), 0x34);
    EXPECT_EQ(getBufferAt(4), 0x12);
}

TEST_F(WiFiMeasurementSerializerTest, SerializesUint32Measurement)
{
    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3,
        static_cast<std::uint32_t>(0xAABBCCDD));

    std::size_t msgLength = 0;
    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, getDataBuffer(), msgLength);

    static constexpr std::size_t EXPECTED_LENGTH = 2U + 1U + 4U + 4U;

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, EXPECTED_LENGTH);
    EXPECT_EQ(getBufferAt(2), static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3));
    EXPECT_EQ(getBufferAt(3), 0xDD);
    EXPECT_EQ(getBufferAt(4), 0xCC);
    EXPECT_EQ(getBufferAt(5), 0xBB);
    EXPECT_EQ(getBufferAt(6), 0xAA);
}

TEST_F(WiFiMeasurementSerializerTest, HandlesBufferTooSmall)
{
    std::array<std::uint8_t, 3U> smallBuffer = {0};
    std::size_t msgLength = 0;

    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3,
        static_cast<std::uint32_t>(0x12345678));

    // Pass smallBuffer directly as an array
    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, smallBuffer, msgLength);

    EXPECT_FALSE(status);
    EXPECT_EQ(msgLength, 0);
}

TEST_F(WiFiMeasurementSerializerTest, HandlesZeroBuffer)
{
    std::array<std::uint8_t, 0U> zeroBuffer = {};
    std::size_t msgLength = 0;

    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1,
        static_cast<std::uint8_t>(0x42));

    const bool status = Device::WiFiMeasurementSerializer::generate(measurement, zeroBuffer, msgLength);

    EXPECT_FALSE(status);
    EXPECT_EQ(msgLength, 0);
}