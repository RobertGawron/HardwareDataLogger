#ifndef Crc32_hpp
#define Crc32_hpp

#include <cstdint>
#include <cstddef>

namespace Device
{
    class Crc32
    {
    public:
        /**
         * @brief Computes the CRC32 checksum of the given data.
         *
         * @param data Pointer to the data buffer.
         * @param length Length of the data buffer in bytes.
         * @return The computed CRC32 checksum.
         */
        static std::uint32_t compute(const uint8_t *data, std::size_t length);
    };
}

#endif // Crc32_hpp
