#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <cstdint>

class test_WiFiMeasurementSerializer : public ::testing::Test
{
protected:
    Device::WiFiMeasurementSerializer messageGenerator;
    static constexpr std::size_t BufferSize = 128;
    std::array<std::uint8_t, BufferSize> dataBuffer = {0};

    Device::MeasurementType createMeasurement(Device::MeasurementDeviceId id, std::variant<std::uint8_t, std::uint16_t, std::uint32_t> value)
    {
        Device::MeasurementType measurement;
        measurement.source = id;
        measurement.data = value;
        return measurement;
    }
};

TEST_F(test_WiFiMeasurementSerializer, SerializesUint8Measurement)
{
    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1,
        static_cast<std::uint8_t>(0xAB));

    std::size_t msgLength = 0;
    bool status = messageGenerator.generate(measurement, dataBuffer.data(), dataBuffer.size(), msgLength);

    constexpr std::size_t lengthHeaderSize = 2;
    constexpr std::size_t sourceIdSize = 1;
    constexpr std::size_t dataSize = 1;
    constexpr std::size_t crcSize = 4;
    constexpr std::size_t expectedLength = lengthHeaderSize + sourceIdSize + dataSize + crcSize;

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, expectedLength);
    EXPECT_EQ(dataBuffer[2], static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1));
    EXPECT_EQ(dataBuffer[3], 0xAB);
}

TEST_F(test_WiFiMeasurementSerializer, SerializesUint16Measurement)
{
    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2,
        static_cast<std::uint16_t>(0x1234));

    std::size_t msgLength = 0;
    bool status = messageGenerator.generate(measurement, dataBuffer.data(), dataBuffer.size(), msgLength);

    constexpr std::size_t lengthHeaderSize = 2;
    constexpr std::size_t sourceIdSize = 1;
    constexpr std::size_t dataSize = 2;
    constexpr std::size_t crcSize = 4;
    constexpr std::size_t expectedLength = lengthHeaderSize + sourceIdSize + dataSize + crcSize;

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, expectedLength);
    EXPECT_EQ(dataBuffer[2], static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2));
    EXPECT_EQ(dataBuffer[3], 0x34);
    EXPECT_EQ(dataBuffer[4], 0x12);
}

TEST_F(test_WiFiMeasurementSerializer, SerializesUint32Measurement)
{
    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3,
        static_cast<std::uint32_t>(0xAABBCCDD));

    std::size_t msgLength = 0;
    bool status = messageGenerator.generate(measurement, dataBuffer.data(), dataBuffer.size(), msgLength);

    constexpr std::size_t lengthHeaderSize = 2;
    constexpr std::size_t sourceIdSize = 1;
    constexpr std::size_t dataSize = 4;
    constexpr std::size_t crcSize = 4;
    constexpr std::size_t expectedLength = lengthHeaderSize + sourceIdSize + dataSize + crcSize;

    EXPECT_TRUE(status);
    EXPECT_EQ(msgLength, expectedLength);
    EXPECT_EQ(dataBuffer[2], static_cast<std::uint8_t>(Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3));
    EXPECT_EQ(dataBuffer[3], 0xDD);
    EXPECT_EQ(dataBuffer[4], 0xCC);
    EXPECT_EQ(dataBuffer[5], 0xBB);
    EXPECT_EQ(dataBuffer[6], 0xAA);
}

TEST_F(test_WiFiMeasurementSerializer, HandlesBufferTooSmall)
{
    std::array<std::uint8_t, 3> smallBuffer = {0};
    std::size_t msgLength = 0;

    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3,
        static_cast<std::uint32_t>(0x12345678));

    bool status = messageGenerator.generate(measurement, smallBuffer.data(), smallBuffer.size(), msgLength);

    EXPECT_FALSE(status);
    EXPECT_EQ(msgLength, 0);
}

TEST_F(test_WiFiMeasurementSerializer, HandlesZeroBuffer)
{
    std::array<std::uint8_t, 0> zeroBuffer = {};
    std::size_t msgLength = 0;

    auto measurement = createMeasurement(
        Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1,
        static_cast<std::uint8_t>(0x42));

    bool status = messageGenerator.generate(measurement, zeroBuffer.data(), zeroBuffer.size(), msgLength);

    EXPECT_FALSE(status);
    EXPECT_EQ(msgLength, 0);
}
