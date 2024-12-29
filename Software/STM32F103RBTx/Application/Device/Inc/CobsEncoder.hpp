#ifndef CobsEncoder_hpp
#define CobsEncoder_hpp

#include <cstddef> // For size_t
#include <cstdint> // For uint8_t

namespace Device
{
    class CobsEncoder
    {
    public:
        // Encode input data into a COBS buffer.
        // Return the number of bytes written into output.
        static std::size_t encode(const uint8_t *input, std::size_t length,
                                  uint8_t *output, std::size_t maxOutputLength);

        // Decode COBS buffer back into original bytes.
        // Return the number of bytes placed into output.
        static std::size_t decode(const uint8_t *input, std::size_t length,
                                  uint8_t *output, std::size_t maxOutputLength);
    };

}

#endif // CobsEncoder_hpp
