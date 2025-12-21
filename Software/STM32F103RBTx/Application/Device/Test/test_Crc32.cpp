#include "Device/Inc/Crc32.hpp"
#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

TEST(Crc32Test, ComputesCrcForEmptyData)
{
    Device::Crc32 crc32;
    const uint8_t data[] = {};
    std::uint32_t result = crc32.compute(data, 0);

    // CRC32 of empty input with init 0xFFFFFFFF and final XOR ~crc is 0x00000000
    EXPECT_EQ(result, 0x00000000);
}

TEST(Crc32Test, ComputesCrcForKnownString)
{
    Device::Crc32 crc32;
    const char *input = "123456789";
    std::uint32_t result = crc32.compute(reinterpret_cast<const uint8_t *>(input), std::strlen(input));

    // Standard CRC32 for "123456789"
    EXPECT_EQ(result, 0xCBF43926);
}

TEST(Crc32Test, ComputesCrcForSingleByte)
{
    Device::Crc32 crc32;
    const uint8_t data[] = {0x00};
    std::uint32_t result = crc32.compute(data, 1);

    // Precomputed CRC32 for 0x00 with standard config
    EXPECT_EQ(result, 0xD202EF8D);
}

TEST(Crc32Test, ComputesCrcForMultipleBytes)
{
    Device::Crc32 crc32;
    const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    std::uint32_t result = crc32.compute(data, sizeof(data));

    // Verified CRC32 for {0xDE, 0xAD, 0xBE, 0xEF}
    EXPECT_EQ(result, 0x7C9CA35A);
}