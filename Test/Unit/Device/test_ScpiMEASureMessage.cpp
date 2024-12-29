#include "Device/Inc/ScpiMEASureMessage.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <cstdint>

namespace Device
{

    class ScpiMEASureMessageTest : public ::testing::Test
    {
    protected:
        static constexpr std::size_t BufferSize = 128;
        ScpiMEASureMessage<BufferSize> messageGenerator;
        std::array<std::uint8_t, BufferSize> dataBuffer = {0};
        std::size_t dataIndex = 0;

        MeasurementType createMeasurement(MeasurementDeviceId id, std::variant<std::uint8_t, std::uint16_t, std::uint32_t> value)
        {
            MeasurementType measurement;
            measurement.source = id;
            measurement.data = value;
            return measurement;
        }
    };

    TEST_F(ScpiMEASureMessageTest, HandlesBufferOverflow)
    {
        std::array<std::uint8_t, 16> smallBuffer = {0};
        std::size_t smallDataIndex = 0;
        ScpiMEASureMessage<16> smallMessageGenerator;

        auto measurement = createMeasurement(
            MeasurementDeviceId::DEVICE_PULSE_COUNTER_3,
            static_cast<std::uint32_t>(123456789));

        EXPECT_FALSE(smallMessageGenerator.generateMessage(
            measurement,
            smallBuffer,
            smallDataIndex));

        EXPECT_EQ(smallDataIndex, 0);
    }

    TEST_F(ScpiMEASureMessageTest, GeneratesMessageWithLargeUint32Value)
    {
        auto measurement = createMeasurement(
            MeasurementDeviceId::DEVICE_UART_1,
            static_cast<std::uint32_t>(4294967295)); // Maximum uint32_t value

        ASSERT_TRUE(messageGenerator.generateMessage(
            measurement,
            dataBuffer,
            dataIndex));

        std::string result(
            dataBuffer.begin(),
            dataBuffer.begin() + dataIndex);

        EXPECT_NE(result.find("MEASure:DEVICE05:DATA \"2024-12-28T11:16:36Z,4294967295"), std::string::npos);
    }

    TEST_F(ScpiMEASureMessageTest, HandlesEmptyMeasurement)
    {
        MeasurementType measurement;
        measurement.source = MeasurementDeviceId::DEVICE_PULSE_COUNTER_1;

        ASSERT_FALSE(messageGenerator.generateMessage(
            measurement,
            dataBuffer,
            dataIndex));

        EXPECT_EQ(dataIndex, 0);
    }

    TEST_F(ScpiMEASureMessageTest, HandlesWrongDeviceId)
    {
        auto measurement = createMeasurement(
            static_cast<MeasurementDeviceId>(999),
            static_cast<std::uint8_t>(1));

        ASSERT_FALSE(messageGenerator.generateMessage(
            measurement,
            dataBuffer,
            dataIndex));

        EXPECT_EQ(dataIndex, 0);
    }

    TEST_F(ScpiMEASureMessageTest, GeneratesValidMessageForBoundaryUint16)
    {
        auto measurement = createMeasurement(
            MeasurementDeviceId::DEVICE_PULSE_COUNTER_4,
            static_cast<std::uint16_t>(65535)); // Maximum uint16_t value

        ASSERT_TRUE(messageGenerator.generateMessage(
            measurement,
            dataBuffer,
            dataIndex));

        std::string result(
            dataBuffer.begin(),
            dataBuffer.begin() + dataIndex);

        EXPECT_NE(result.find("MEASure:DEVICE04:DATA \"2024-12-28T11:16:36Z,65535"), std::string::npos);
    }

} // namespace Device
