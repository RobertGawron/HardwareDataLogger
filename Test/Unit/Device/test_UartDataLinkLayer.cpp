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
        UartDataLinkLayer<InputBufferSize, OutputBufferSize> dataLinkLayer;
        std::array<std::uint8_t, InputBufferSize> inputBuffer = {0};
        std::array<std::uint8_t, OutputBufferSize> outputBuffer = {0};
        std::size_t inputLength = 10;
        std::size_t outputLength = OutputBufferSize;

        void initializeInput()
        {
            inputBuffer.fill(0x55);
        }

        void initializeInput(const std::string &message)
        {
            inputLength = message.size();

            ASSERT_LT(
                inputLength + dataLinkLayer.HeaderLength + dataLinkLayer.CrcFieldSize,
                InputBufferSize);

            for (std::size_t i = 0; i < inputLength; ++i)
            {
                inputBuffer[dataLinkLayer.HeaderLength + i] = static_cast<std::uint8_t>(message[i]);
            }
        }

        std::uint32_t computeCrc(
            const std::array<std::uint8_t, InputBufferSize> &buffer,
            std::size_t length)
        {
            Crc32 crc;
            return crc.compute(buffer.data(), length);
        }

        std::size_t encodeMessage(
            const std::array<std::uint8_t, InputBufferSize> &input,
            std::size_t length,
            std::array<std::uint8_t, OutputBufferSize> &output)
        {
            CobsEncoder encoder;

            return encoder.encode(
                input.data(),
                length,
                output.data(),
                output.size());
        }

        std::size_t decodeMessage(
            const std::array<std::uint8_t, OutputBufferSize> &encodedBuffer,
            std::size_t encodedLength,
            std::array<std::uint8_t, InputBufferSize> &decodedBuffer)
        {
            CobsEncoder encoder;

            return encoder.decode(
                encodedBuffer.data(),
                encodedLength,
                decodedBuffer.data(),
                decodedBuffer.size());
        }
    };

    TEST_F(UartDataLinkLayerTest, GeneratesMessageSuccessfully)
    {
        initializeInput();

        bool result = dataLinkLayer.generate(inputBuffer, inputLength, outputBuffer, outputLength);

        ASSERT_TRUE(result);

        // Validate CRC is correctly placed
        std::uint32_t computedCrc = computeCrc(inputBuffer, dataLinkLayer.HeaderLength + inputLength);
        std::uint32_t embeddedCrc = (static_cast<std::uint32_t>(inputBuffer[2 + inputLength]) << 24) |
                                    (static_cast<std::uint32_t>(inputBuffer[3 + inputLength]) << 16) |
                                    (static_cast<std::uint32_t>(inputBuffer[4 + inputLength]) << 8) |
                                    (static_cast<std::uint32_t>(inputBuffer[5 + inputLength]));

        EXPECT_EQ(computedCrc, embeddedCrc);

        // Validate encoded message
        std::size_t encodedSize = encodeMessage(
            inputBuffer,
            inputLength,
            outputBuffer);

        ASSERT_GT(encodedSize, 0);
    }

    TEST_F(UartDataLinkLayerTest, HandlesZeroInputLength)
    {
        inputLength = 0;

        bool result = dataLinkLayer.generate(
            inputBuffer,
            inputLength,
            outputBuffer,
            outputLength);

        ASSERT_FALSE(result);
    }

    TEST_F(UartDataLinkLayerTest, HandlesExactBufferSizeWithScpiMessage)
    {
        // Initialize with SCPI message
        std::string scpiMessage = "This is dummy SCPI message 555";
        initializeInput(scpiMessage);

        std::cout << "Initially Encoded Buffer len = " << dataLinkLayer.HeaderLength + inputLength << ": ";
        for (std::size_t i = 0; i < (dataLinkLayer.HeaderLength + inputLength); ++i)
        {
            std::cout << std::hex << i << ":" << static_cast<int>(inputBuffer[i]) << " ";
        }
        std::cout << std::dec << std::endl;

        // Generate encoded message
        bool result = dataLinkLayer.generate(
            inputBuffer,
            inputLength,
            outputBuffer,
            outputLength);

        ASSERT_TRUE(result);

        // Decode the message back
        std::array<std::uint8_t, InputBufferSize> decodedBuffer = {0};
        std::size_t decodedLength = decodeMessage(
            outputBuffer,
            outputLength,
            decodedBuffer);

        // Debugging Output
        std::cout << "Encoded Buffer len = " << outputLength << ": ";
        for (std::size_t i = 0; i < outputLength; ++i)
        {
            std::cout << std::hex << static_cast<int>(outputBuffer[i]) << " ";
        }
        std::cout << std::dec << std::endl;

        ASSERT_GT(decodedLength, 0);

        std::size_t msgLengthFromHeader = (decodedBuffer[0] << 8) | decodedBuffer[1];
        EXPECT_EQ(msgLengthFromHeader, inputLength + dataLinkLayer.HeaderLength);

        // Debugging Output for Decoded Buffer
        std::cout << "Decoded Buffer: ";
        for (std::size_t i = 2; i < msgLengthFromHeader; ++i)
        {
            std::cout << std::hex << static_cast<char>(decodedBuffer[i]) << ".";
        }
        std::cout << std::dec << std::endl;

        // Verify CRC
        std::uint32_t computedCrc = computeCrc(decodedBuffer, inputLength + dataLinkLayer.HeaderLength);
        std::uint32_t embeddedCrc = (static_cast<std::uint32_t>(decodedBuffer[inputLength + dataLinkLayer.HeaderLength]) << 24) |
                                    (static_cast<std::uint32_t>(decodedBuffer[inputLength + dataLinkLayer.HeaderLength + 1]) << 16) |
                                    (static_cast<std::uint32_t>(decodedBuffer[inputLength + dataLinkLayer.HeaderLength + 2]) << 8) |
                                    (static_cast<std::uint32_t>(decodedBuffer[inputLength + dataLinkLayer.HeaderLength + 3]));

        EXPECT_EQ(computedCrc, embeddedCrc);

        // Verify message data
        std::string extractedMessage(decodedBuffer.begin() + dataLinkLayer.HeaderLength,
                                     decodedBuffer.begin() + dataLinkLayer.HeaderLength + inputLength);
        EXPECT_EQ(extractedMessage, scpiMessage);
    }

    TEST_F(UartDataLinkLayerTest, HandlesInvalidInputLength)
    {
        inputLength = InputBufferSize + 10; // Exceed buffer size

        bool result = dataLinkLayer.generate(
            inputBuffer,
            inputLength,
            outputBuffer,
            outputLength);

        ASSERT_FALSE(result);
    }

    TEST_F(UartDataLinkLayerTest, EncodesEmptyMessageCorrectly)
    {
        inputLength = 0;

        bool result = dataLinkLayer.generate(
            inputBuffer,
            inputLength,
            outputBuffer,
            outputLength);

        ASSERT_FALSE(result);
    }

    TEST_F(UartDataLinkLayerTest, DetectsIncorrectEncoding)
    {
        initializeInput();

        bool result = dataLinkLayer.generate(
            inputBuffer,
            inputLength,
            outputBuffer,
            outputLength);

        ASSERT_TRUE(result);

        // Manually corrupt encoded message
        outputBuffer[5] = 0xFF;

        std::size_t encodedSize = encodeMessage(
            inputBuffer,
            inputLength,
            outputBuffer);

        EXPECT_NE(encodedSize, outputLength);
    }

} // namespace Device
