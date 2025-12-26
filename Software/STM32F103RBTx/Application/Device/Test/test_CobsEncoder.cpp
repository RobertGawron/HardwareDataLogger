#include "Device/Inc/CobsEncoder.hpp"

#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include <cstddef>   // For std::size_t
#include <iostream>  // For std::cout
#include <iomanip>   // For std::hex, std::dec, std::setw, std::setfill
#include <algorithm> // For std::equal

class CobsEncoderTest : public ::testing::Test
{
private:
    static constexpr std::size_t MAX_BUFFER_SIZE = 300U;
    std::array<std::uint8_t, MAX_BUFFER_SIZE> encodeBuffer{};

public:
    std::array<std::uint8_t, MAX_BUFFER_SIZE> &getEncodeBuffer() { return encodeBuffer; }
};

TEST_F(CobsEncoderTest, EncodeDecodeEmptyData)
{
    static constexpr std::size_t EMPTY_INPUT_SIZE = 1U; // Minimum size to avoid zero-length array
    static constexpr std::size_t EMPTY_INPUT_LENGTH = 0U;
    static constexpr std::size_t EXPECTED_OUTPUT_SIZE = 2U;
    static constexpr std::uint8_t EXPECTED_CODE_BYTE = 0x01U;
    static constexpr std::uint8_t EXPECTED_DELIMITER = 0x00U;
    static constexpr int HEX_WIDTH = 2;
    static constexpr char HEX_FILL = '0';
    const std::array<std::uint8_t, EMPTY_INPUT_SIZE> input{};
    auto result = Device::CobsEncoder::encode(input, EMPTY_INPUT_LENGTH, getEncodeBuffer());
    ASSERT_TRUE(result.has_value());
    const std::size_t encodedSize = result.value_or(0U); // Provides default value
    // Print the encoded buffer data
    std::cout << "Encoded Data: ";
    for (std::size_t i = 0U; i < encodedSize; ++i)
    {
        std::cout << std::hex << std::setw(HEX_WIDTH) << std::setfill(HEX_FILL)
                  << static_cast<int>(getEncodeBuffer()[i]) << " ";
    }
    std::cout << std::dec << '\n';
    // Empty data encodes to {0x01, 0x00}
    const std::uint8_t output[] = {EXPECTED_CODE_BYTE, EXPECTED_DELIMITER};
    // Check if the encoded message matches the expected output
    EXPECT_EQ(encodedSize, EXPECTED_OUTPUT_SIZE);
    EXPECT_TRUE(std::equal(std::begin(output), std::end(output), getEncodeBuffer().begin()));
}

TEST_F(CobsEncoderTest, HandlesInsufficientEncodeBuffer)
{
    static constexpr std::size_t INPUT_SIZE = 10U;
    static constexpr std::size_t SMALL_BUFFER_SIZE = 5U;
    static constexpr std::uint8_t TEST_FILL_VALUE = 0x55U;

    std::array<std::uint8_t, INPUT_SIZE> input{};
    std::fill(input.begin(), input.end(), TEST_FILL_VALUE);
    std::array<std::uint8_t, SMALL_BUFFER_SIZE> smallBuffer{};
    auto result = Device::CobsEncoder::encode(input, input.size(), smallBuffer);

    EXPECT_FALSE(result.has_value());
}
