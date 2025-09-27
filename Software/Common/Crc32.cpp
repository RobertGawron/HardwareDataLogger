#include "Crc32.hpp"

#include <cstdint>
#include <cstddef>

namespace Device
{
    namespace
    {
        constexpr std::uint32_t INITIAL_CRC = 0xFFFFFFFF;
        constexpr std::uint32_t POLYNOMIAL = 0xEDB88320;
        constexpr std::size_t BITS_PER_BYTE = 8;
    }

    std::uint32_t Crc32::compute(const uint8_t *data, std::size_t length)
    {
        std::uint32_t crc = INITIAL_CRC;
        for (std::size_t i = 0; i < length; ++i)
        {
            crc ^= data[i];
            for (std::size_t j = 0; j < BITS_PER_BYTE; ++j)
            {
                if ((crc & 1) != 0) // Explicitly check if the least significant bit is set
                {
                    crc = (crc >> 1) ^ POLYNOMIAL;
                }
                else
                {
                    crc >>= 1;
                }
            }
        }
        return ~crc;
    }
}
