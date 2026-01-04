#include "Device/Inc/Crc32.hpp"

#include <gtest/gtest.h>
#include <cstdint>
#include <array>
#include <span>

namespace
{
    // CRC constants
    constexpr std::uint32_t EXPECTED_EMPTY_CRC = 0x00000000U;
    constexpr std::uint32_t EXPECTED_STRING_CRC = 0xCBF43926U;
    constexpr std::uint32_t EXPECTED_SINGLE_BYTE_CRC = 0xD202EF8DU;
    constexpr std::uint32_t EXPECTED_MULTIPLE_BYTES_CRC = 0x7C9CA35AU;
}

TEST(Crc32Test, ComputesCrcForEmptyData)
{
    // Empty span
    const std::array<std::uint8_t, 1> data = {0x00U};

    const std::uint32_t result = Device::Crc32::compute(std::span<const std::uint8_t>{data.data(), 0});

    EXPECT_EQ(result, EXPECTED_EMPTY_CRC);
}

TEST(Crc32Test, ComputesCrcForKnownString)
{
    // Standard CRC32 for "123456789"
    const std::array<std::uint8_t, 9> data = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    const std::uint32_t result = Device::Crc32::compute(std::span{data});

    EXPECT_EQ(result, EXPECTED_STRING_CRC);
}

TEST(Crc32Test, ComputesCrcForSingleByte)
{
    const std::array<std::uint8_t, 1> data = {0x00U};

    const std::uint32_t result = Device::Crc32::compute(std::span{data});

    EXPECT_EQ(result, EXPECTED_SINGLE_BYTE_CRC);
}

TEST(Crc32Test, ComputesCrcForMultipleBytes)
{
    const std::array<std::uint8_t, 4> data = {0xDEU, 0xADU, 0xBEU, 0xEFU};

    const std::uint32_t result = Device::Crc32::compute(std::span{data});

    EXPECT_EQ(result, EXPECTED_MULTIPLE_BYTES_CRC);
}

TEST(Crc32Test, ComputesCrcForPartialArray)
{
    // Test using only part of an array
    const std::array<std::uint8_t, 9> data = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Only compute CRC for first 5 bytes
    const std::uint32_t result = Device::Crc32::compute(std::span{data.data(), 5});

    // CRC for "12345"
    EXPECT_NE(result, EXPECTED_STRING_CRC); // Should be different from full string
}
