#ifndef Crc32_hpp
#define Crc32_hpp

#include <cstddef> // For size_t
#include <cstdint> // For uint8_t

namespace Device
{
    class Crc32
    {
    public:
        std::uint32_t compute(const uint8_t *data, std::size_t length);
    };
}

#endif // Crc32_hpp
