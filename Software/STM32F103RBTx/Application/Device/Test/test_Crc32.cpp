#include "Device/Inc/Crc32.hpp"

#include <gtest/gtest.h>
#include <cstdint>
#include <array>
#include <cstddef>

namespace
{
    // CRC constants
    constexpr std::uint32_t EXPECTED_EMPTY_CRC = 0x00000000U;
    constexpr std::uint32_t EXPECTED_STRING_CRC = 0xCBF43926U;
    constexpr std::uint32_t EXPECTED_SINGLE_BYTE_CRC = 0xD202EF8DU;
    constexpr std::uint32_t EXPECTED_MULTIPLE_BYTES_CRC = 0x7C9CA35AU;

    constexpr std::size_t LENGTH_ZERO = 0U;
    constexpr std::size_t LENGTH_ONE = 1U;
}

TEST(Crc32Test, ComputesCrcForEmptyData)
{
    // Pass as length 0 using std::array
    static constexpr std::size_t ARRAY_SIZE = 1U;
    const std::array<std::uint8_t, ARRAY_SIZE> data = {0x00U};

    const std::uint32_t result = Device::Crc32::compute(data, LENGTH_ZERO);

    EXPECT_EQ(result, EXPECTED_EMPTY_CRC);
}

TEST(Crc32Test, ComputesCrcForKnownString)
{
    // Standard CRC32 for "123456789"
    static constexpr std::size_t STRING_SIZE = 9U;
    const std::array<std::uint8_t, STRING_SIZE> data = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    const std::uint32_t result = Device::Crc32::compute(data, STRING_SIZE);

    EXPECT_EQ(result, EXPECTED_STRING_CRC);
}

TEST(Crc32Test, ComputesCrcForSingleByte)
{
    static constexpr std::size_t ARRAY_SIZE = 1U;
    const std::array<std::uint8_t, ARRAY_SIZE> data = {0x00U};

    const std::uint32_t result = Device::Crc32::compute(data, LENGTH_ONE);

    EXPECT_EQ(result, EXPECTED_SINGLE_BYTE_CRC);
}

TEST(Crc32Test, ComputesCrcForMultipleBytes)
{
    static constexpr std::size_t ARRAY_SIZE = 4U;
    const std::array<std::uint8_t, ARRAY_SIZE> data = {0xDEU, 0xADU, 0xBEU, 0xEFU};

    const std::uint32_t result = Device::Crc32::compute(data, ARRAY_SIZE);

    EXPECT_EQ(result, EXPECTED_MULTIPLE_BYTES_CRC);
}
