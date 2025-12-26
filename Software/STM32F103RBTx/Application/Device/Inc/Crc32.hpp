#ifndef Crc32_hpp
#define Crc32_hpp

#include <cstdint>
#include <cstddef>
#include <array>
#include <algorithm> // Required for std::for_each
#include <iterator>  // Required for std::next

namespace Device
{
    class Crc32
    {
    public:
        // Constants using UPPERCASE_WITH_UNDERSCORES
        static constexpr std::uint32_t INITIAL_REMAINDER = 0xFFFFFFFFU;
        static constexpr std::uint32_t FINAL_XOR_VALUE = 0xFFFFFFFFU;
        static constexpr std::uint32_t POLYNOMIAL = 0xEDB88320U;
        static constexpr std::uint8_t BITS_PER_BYTE = 8U;
        static constexpr std::uint32_t LSB_MASK = 1U;

        /**
         * @brief Computes the CRC32 checksum of a specific length within a std::array.
         *
         * @tparam SIZE The full size of the array.
         * @param data The array containing the data.
         * @param length The number of bytes to process.
         * @return The computed CRC32 checksum.
         */
        template <std::size_t SIZE>
        static std::uint32_t compute(const std::array<std::uint8_t, SIZE> &data, std::size_t length)
        {
            std::uint32_t crc = INITIAL_REMAINDER;

            // Ensure we don't exceed the actual array bounds
            const std::size_t effective_length = (length > SIZE) ? SIZE : length;

            // Use iterators instead of indices or raw pointers.
            // std::next is a safe way to get the 'end' iterator for the sub-range.
            const auto start = data.begin();

            const auto end = std::next(start,
                                       static_cast<typename std::array<std::uint8_t, SIZE>::difference_type>(effective_length));

            std::for_each(start, end, [&](const std::uint8_t byte)
                          { crc = update_crc(crc, byte); });

            return crc ^ FINAL_XOR_VALUE;
        }

    private:
        /**
         * @brief Processes a single byte to update the CRC remainder.
         */
        static constexpr std::uint32_t update_crc(std::uint32_t crc, std::uint8_t byte)
        {
            crc ^= static_cast<std::uint32_t>(byte);

            for (std::uint8_t i = 0U; i < BITS_PER_BYTE; ++i)
            {
                const bool is_lsb_set = (crc & LSB_MASK) != 0U;
                crc >>= 1U;
                if (is_lsb_set)
                {
                    crc ^= POLYNOMIAL;
                }
            }
            return crc;
        }
    };
}

#endif // Crc32_hpp
