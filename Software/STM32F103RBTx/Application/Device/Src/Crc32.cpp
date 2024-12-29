
#include "Device/Inc/Crc32.hpp"

namespace Device
{
    std::uint32_t Crc32::compute(const uint8_t *data, std::size_t length)
    {
        std::uint32_t crc = 0xFFFFFFFF;
        for (std::size_t i = 0; i < length; ++i)
        {
            crc ^= data[i];
            for (std::size_t j = 0; j < 8; ++j)
            {
                if (crc & 1)
                {
                    crc = (crc >> 1) ^ 0xEDB88320; // Standard polynomial
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
