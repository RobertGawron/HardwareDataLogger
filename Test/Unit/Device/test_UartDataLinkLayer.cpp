#include "Device/Inc/UartDataLinkLayer.hpp"
#include <gtest/gtest.h>
#include <array>
#include <cstdint>

namespace Device
{

    class UartDataLinkLayerTest : public ::testing::Test
    {
    protected:
        static constexpr std::size_t InputBufferSize = 64;
        static constexpr std::size_t OutputBufferSize = 128;
        UartDataLinkLayer<InputBufferSize, OutputBufferSize> uartLayer;
        std::array<std::uint8_t, InputBufferSize> inputBuffer = {0};
        std::array<std::uint8_t, OutputBufferSize> outputBuffer = {0};
        std::size_t inputLength = 10;
        std::size_t outputLength = OutputBufferSize;

        void initializeInput()
        {
            for (std::size_t i = uartLayer.msgStart(); i < InputBufferSize; ++i)
            {
                inputBuffer[i] = static_cast<std::uint8_t>(i);
            }
        }
    };

    TEST_F(UartDataLinkLayerTest, GeneratesMessageSuccessfully)
    {
        initializeInput();

        bool result = uartLayer.generateMessage(inputBuffer, inputLength, outputBuffer, outputLength);

        ASSERT_TRUE(result);

        // Validate CRC is correctly placed
        std::uint32_t computedCrc = uartLayer.crc.compute(inputBuffer.data(), uartLayer.msgStart() + inputLength);
        std::uint32_t embeddedCrc = (static_cast<std::uint32_t>(inputBuffer[2 + inputLength]) << 24) |
                                    (static_cast<std::uint32_t>(inputBuffer[3 + inputLength]) << 16) |
                                    (static_cast<std::uint32_t>(inputBuffer[4 + inputLength]) << 8) |
                                    (static_cast<std::uint32_t>(inputBuffer[5 + inputLength]));

        // Print CRC values for debugging
        std::cout << "Computed CRC: " << std::hex << computedCrc << std::endl;
        std::cout << "Embedded CRC: " << std::hex << embeddedCrc << std::endl;

        EXPECT_EQ(computedCrc, embeddedCrc);

        // Validate encoded message
        std::size_t encodedSize = uartLayer.encoder.encode(inputBuffer.data(), inputLength, outputBuffer.data(), outputLength);
        ASSERT_GT(encodedSize, 0);
    }

    TEST_F(UartDataLinkLayerTest, HandlesBufferOverflow)
    {
        std::array<std::uint8_t, 8> smallOutputBuffer = {0};
        std::size_t smallOutputLength = smallOutputBuffer.size();

        initializeInput();

        // bool result = uartLayer.generateMessage(inputBuffer, inputLength, smallOutputBuffer, smallOutputLength);

        //        ASSERT_FALSE(result);
    }

    TEST_F(UartDataLinkLayerTest, HandlesZeroInputLength)
    {
        inputLength = 0;

        bool result = uartLayer.generateMessage(inputBuffer, inputLength, outputBuffer, outputLength);

        ASSERT_FALSE(result);
    }

    TEST_F(UartDataLinkLayerTest, HandlesInvalidCrcComputation)
    {
        initializeInput();

        // Corrupt the input data before generating the message
        inputBuffer[10] = 0xFF;

        bool result = uartLayer.generateMessage(inputBuffer, inputLength, outputBuffer, outputLength);

        ASSERT_TRUE(result);

        std::uint32_t computedCrc = uartLayer.crc.compute(inputBuffer.data(), uartLayer.msgStart() + inputLength);
        std::uint32_t embeddedCrc = (static_cast<std::uint32_t>(inputBuffer[2]) << 24) |
                                    (static_cast<std::uint32_t>(inputBuffer[3]) << 16) |
                                    (static_cast<std::uint32_t>(inputBuffer[4]) << 8) |
                                    (static_cast<std::uint32_t>(inputBuffer[5]));

        EXPECT_NE(computedCrc, embeddedCrc);
    }

    TEST_F(UartDataLinkLayerTest, HandlesEmptyInput)
    {
        inputBuffer.fill(0);

        bool result = uartLayer.generateMessage(inputBuffer, inputLength, outputBuffer, outputLength);

        ASSERT_TRUE(result);

        // Validate encoded message
        std::size_t encodedSize = uartLayer.encoder.encode(inputBuffer.data(), inputLength, outputBuffer.data(), outputLength);
        ASSERT_GT(encodedSize, 0);
    }

} // namespace Device
