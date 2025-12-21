#include "Device/Inc/CobsEncoder.hpp"

#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <iostream>  // For std::cout
#include <iomanip>   // For std::hex, std::dec, std::setw, std::setfill
#include <algorithm> // For std::equal

class CobsEncoderTest : public ::testing::Test
{
public:
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
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(encodeBuffer[i]) << " ";
    }
    std::cout << std::dec << '\n';

    // CORRECTED: Empty data encodes to {0x01, 0x00}
    std::uint8_t output[] = {0x01, 0x00};

    // Check if the encoded message matches the expected output
    EXPECT_EQ(encodedSize, sizeof(output));
    EXPECT_TRUE(std::equal(std::begin(output), std::end(output), encodeBuffer.begin()));
}

TEST_F(CobsEncoderTest, HandlesInsufficientEncodeBuffer)
{
    std::uint8_t input[10];
    std::fill_n(input, 10, 0x55);
    std::array<std::uint8_t, 5> smallBuffer{};
    auto encodedSize = encoder.encode(input, sizeof(input), smallBuffer.data(), smallBuffer.size());
    EXPECT_EQ(encodedSize, 0);
}
