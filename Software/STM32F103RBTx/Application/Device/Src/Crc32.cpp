#include "Device/Inc/Crc32.hpp"

#include <cstdint>
#include <cstddef>
#include <iterator> // for std::next
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

        // C++17: Calculate end pointer using std::next to avoid raw arithmetic warnings
        const auto *end = std::next(data, length);

        // Iterate using pointers instead of index 'data[i]'
        for (auto *it = data; it != end; ++it)
        {
            crc ^= *it;

            for (std::size_t j = 0; j < BITS_PER_BYTE; ++j)
            {
                const bool isLsbSet = (crc & 1) != 0;

                // Always shift right
                crc >>= 1;

                // Apply polynomial only if LSB was set
                if (isLsbSet)
                {
                    crc ^= POLYNOMIAL;
                }
            }
        }
        //
        return ~crc;
    }
}
