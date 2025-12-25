#include "Device/Inc/Crc32.hpp"

#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

TEST(Crc32Test, ComputesCrcForEmptyData)
{
    // pass as length 0, but give one element in array just to avoid static
    // analyze warnings "zero size arrays are an extension"
    const uint8_t data[] = {0x00};
    const std::uint32_t result = Device::Crc32::compute(data, 0);

    // CRC32 of empty input with init 0xFFFFFFFF and final XOR ~crc is 0x00000000
    EXPECT_EQ(result, 0x00000000);
}

TEST(Crc32Test, ComputesCrcForKnownString)
{
    const char *input = "123456789";
    const std::uint32_t result = Device::Crc32::compute(reinterpret_cast<const uint8_t *>(input), std::strlen(input));

    // Standard CRC32 for "123456789"
    EXPECT_EQ(result, 0xCBF43926);
}

TEST(Crc32Test, ComputesCrcForSingleByte)
{
    const uint8_t data[] = {0x00};
    const std::uint32_t result = Device::Crc32::compute(data, 1);

    // Precomputed CRC32 for 0x00 with standard config
    EXPECT_EQ(result, 0xD202EF8D);
}

TEST(Crc32Test, ComputesCrcForMultipleBytes)
{
    const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    const std::uint32_t result = Device::Crc32::compute(data, sizeof(data));

    // Verified CRC32 for {0xDE, 0xAD, 0xBE, 0xEF}
    EXPECT_EQ(result, 0x7C9CA35A);
}
