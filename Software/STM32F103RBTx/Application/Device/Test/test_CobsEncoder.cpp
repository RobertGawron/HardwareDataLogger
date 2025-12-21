#include "Device/Inc/CobsEncoder.hpp"
#include <gtest/gtest.h>
#include <array>
#include <cstdint>

class CobsEncoderTest : public ::testing::Test
{
protected:
    Device::CobsEncoder encoder;
    static constexpr std::size_t MaxBuffer = 300; // Increased buffer to handle worst-case
    std::array<std::uint8_t, MaxBuffer> encodeBuffer{};
};

TEST_F(CobsEncoderTest, EncodeDecodeEmptyData)
{
    std::uint8_t input[] = {};
    auto encodedSize = encoder.encode(input, 0, encodeBuffer.data(), encodeBuffer.size());

    // Print the encoded buffer data
    std::cout << "Encoded Data: ";
    for (std::size_t i = 0; i < encodedSize; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)encodeBuffer[i] << " ";
    }
    std::cout << std::dec << std::endl; // Switch back to decimal after printing hex

    // Create the expected encoded output
    std::uint8_t output[] = {0x00}; // start and stop delimiter

    // Check if the encoded message matches the expected output
    EXPECT_EQ(encodedSize, sizeof(output));
    EXPECT_TRUE(std::equal(std::begin(output), std::end(output), encodeBuffer.begin()));
}

TEST_F(CobsEncoderTest, EncodeDecodeSimpleData)
{
    std::uint8_t input[] = {0x11, 0x22, 0x00, 0x33};
    auto encodedSize = encoder.encode(input, sizeof(input), encodeBuffer.data(), encodeBuffer.size());
    EXPECT_GT(encodedSize, 0);

    // Create the expected encoded output
    std::uint8_t output[] = {3, 17, 34, 2, 51, 0};

    // Check if the encoded message matches the expected output
    EXPECT_EQ(encodedSize, sizeof(output));
    EXPECT_TRUE(std::equal(std::begin(output), std::end(output), encodeBuffer.begin()));

    // Decode directly into the input buffer (no need for a separate decode buffer)
    auto decodedSize = encoder.decode(encodeBuffer.data(), encodedSize);
    EXPECT_EQ(decodedSize, sizeof(input));

    // Ensure the decoded data matches the original input
    EXPECT_TRUE(std::equal(input, input + sizeof(input), encodeBuffer.data()));
}

TEST_F(CobsEncoderTest, EncodeAllNonZeroData)
{
    std::uint8_t input[5];
    std::fill_n(input, 5, 0x55); // Input with 5 bytes of 0x55
    auto encodedSize = encoder.encode(input, sizeof(input), encodeBuffer.data(), encodeBuffer.size());
    EXPECT_GT(encodedSize, 0);

    // Create the correct expected encoded output
    // Leading 0 byte, block length (6), data bytes (5 * 0x55), trailing 0 byte
    std::uint8_t output[] = {0x06, 0x55, 0x55, 0x55, 0x55, 0x55, 0x00};

    // Print the encoded buffer data
    std::cout << "Encoded Data: ";
    for (std::size_t i = 0; i < encodedSize; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)encodeBuffer[i] << " ";
    }
    std::cout << std::dec << std::endl; // Switch back to decimal after printing hex

    // Check if the encoded message matches the expected output
    EXPECT_EQ(encodedSize, sizeof(output));
    EXPECT_TRUE(std::equal(std::begin(output), std::end(output), encodeBuffer.begin()));

    // Decode directly into the input buffer (no need for a separate decode buffer)
    auto decodedSize = encoder.decode(encodeBuffer.data(), encodedSize);
    EXPECT_EQ(decodedSize, sizeof(input));

    // Ensure the decoded data matches the original input
    EXPECT_TRUE(std::equal(input, input + sizeof(input), encodeBuffer.data()));
}

TEST_F(CobsEncoderTest, HandlesInsufficientEncodeBuffer)
{
    std::uint8_t input[10];
    std::fill_n(input, 10, 0x55);
    std::array<std::uint8_t, 5> smallBuffer{};
    auto encodedSize = encoder.encode(input, sizeof(input), smallBuffer.data(), smallBuffer.size());
    EXPECT_EQ(encodedSize, 0);
}

TEST_F(CobsEncoderTest, DecodeHandlesNullInput)
{
    auto decodedSize = encoder.decode(nullptr, 10);
    EXPECT_EQ(decodedSize, 0);
}

TEST_F(CobsEncoderTest, DecodeHandlesNullOutput)
{
    std::uint8_t dummyInput[] = {0x01};
    auto decodedSize = encoder.decode(dummyInput, sizeof(dummyInput));
    EXPECT_EQ(decodedSize, 0);
}

TEST_F(CobsEncoderTest, DecodeHandlesZeroLength)
{
    std::uint8_t dummyInput[] = {0x01};
    auto decodedSize = encoder.decode(dummyInput, 0);
    EXPECT_EQ(decodedSize, 0);
}

TEST_F(CobsEncoderTest, DecodeHandlesMalformedInput)
{
    std::uint8_t malformedInput[] = {0x05, 0x11}; // Code byte too large for available data
    auto decodedSize = encoder.decode(malformedInput, sizeof(malformedInput));
    EXPECT_EQ(decodedSize, 0);
}

TEST_F(CobsEncoderTest, EncodeDecodeRoundTripMatchesOriginal)
{
    std::uint8_t input[] = {0xa, 0xb, 0xc, 0x5, 0x55};
    auto encodedSize = encoder.encode(input, sizeof(input), encodeBuffer.data(), encodeBuffer.size());
    EXPECT_GT(encodedSize, 0);

    // Create the expected encoded output based on the COBS encoding
    std::uint8_t output[] = {6, 10, 11, 12, 5, 85, 0};

    // Check if the encoded message matches the expected output
    EXPECT_EQ(encodedSize, sizeof(output));
    EXPECT_TRUE(std::equal(std::begin(output), std::end(output), encodeBuffer.begin()));

    // Print the encoded buffer data
    std::cout << "Encoded Data: ";
    for (std::size_t i = 0; i < encodedSize; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)encodeBuffer[i] << " ";
    }
    std::cout << std::dec << std::endl; // Switch back to decimal after printing hex

    // Decode directly into the input buffer (no need for a separate decode buffer)
    auto decodedSize = encoder.decode(encodeBuffer.data(), encodedSize);
    EXPECT_EQ(decodedSize, sizeof(input));

    // Ensure the decoded data matches the original input
    EXPECT_TRUE(std::equal(input, input + sizeof(input), encodeBuffer.data()));

    std::cout << "Decoded Data: ";
    for (std::size_t i = 0; i < decodedSize; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)encodeBuffer[i] << " ";
    }
    std::cout << std::dec << std::endl; // Switch back to decimal after printing hex
}
