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
    // Encapsulated fields
    Device::WiFiMeasurementSerializer messageGenerator;
    static constexpr std::size_t BufferSize = 128;
    std::array<std::uint8_t, BufferSize> dataBuffer = {0};

public:
    // Public Getters
    Device::WiFiMeasurementSerializer &getMessageGenerator() { return messageGenerator; }
    std::uint8_t *getDataBufferPtr() { return dataBuffer.data(); }
    std::size_t getDataBufferSize() { return dataBuffer.size(); }

    // Getter for specific index access
    std::uint8_t getBufferAt(std::size_t index) const { return dataBuffer.at(index); }

protected:
    // Helper method remains protected for use in test cases
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
    const bool status = getMessageGenerator().generate(measurement, getDataBufferPtr(), getDataBufferSize(), msgLength);

    constexpr std::size_t expectedLength = 2 + 1 + 1 + 4; // Header + ID + Data + CRC

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, expectedLength);
    EXPECT_EQ(getBufferAt(2), static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1));
    EXPECT_EQ(getBufferAt(3), 0xAB);
}

TEST_F(WiFiMeasurementSerializerTest, SerializesUint16Measurement)
{
    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2,
        static_cast<std::uint16_t>(0x1234));

    std::size_t msgLength = 0;
    const bool status = getMessageGenerator().generate(measurement, getDataBufferPtr(), getDataBufferSize(), msgLength);

    constexpr std::size_t expectedLength = 2 + 1 + 2 + 4;

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, expectedLength);
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
    const bool status = getMessageGenerator().generate(measurement, getDataBufferPtr(), getDataBufferSize(), msgLength);

    constexpr std::size_t expectedLength = 2 + 1 + 4 + 4;

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, expectedLength);
    EXPECT_EQ(getBufferAt(2), static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3));
    EXPECT_EQ(getBufferAt(3), 0xDD);
    EXPECT_EQ(getBufferAt(4), 0xCC);
    EXPECT_EQ(getBufferAt(5), 0xBB);
    EXPECT_EQ(getBufferAt(6), 0xAA);
}

TEST_F(WiFiMeasurementSerializerTest, HandlesBufferTooSmall)
{
    std::array<std::uint8_t, 3> smallBuffer = {0};
    std::size_t msgLength = 0;

    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3,
        static_cast<std::uint32_t>(0x12345678));

    // Note: Here we use the local smallBuffer, not the fixture one
    const bool status = getMessageGenerator().generate(measurement, smallBuffer.data(), smallBuffer.size(), msgLength);

    EXPECT_FALSE(status);
    EXPECT_EQ(msgLength, 0);
}

TEST_F(WiFiMeasurementSerializerTest, HandlesZeroBuffer)
{
    std::array<std::uint8_t, 0> zeroBuffer = {};
    std::size_t msgLength = 0;

    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1,
        static_cast<std::uint8_t>(0x42));

    const bool status = getMessageGenerator().generate(measurement, zeroBuffer.data(), zeroBuffer.size(), msgLength);

    EXPECT_FALSE(status);
    EXPECT_EQ(msgLength, 0);
}
