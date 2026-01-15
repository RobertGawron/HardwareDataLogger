module;

#include <cstdint>
#include <cstddef>
#include <span>

export module Device.Crc32;

export namespace Device
{
    class Crc32 final
    {
    public:
        /**
         * @brief Computes the CRC32 checksum over a span of data.
         *
         * @param data The data to process.
         * @return The computed CRC32 checksum.
         */
        [[nodiscard]] static constexpr std::uint32_t compute(
            std::span<const std::uint8_t> data) noexcept
        {
            std::uint32_t crc = INITIAL_REMAINDER;

            for (const std::uint8_t byte : data)
            {
                crc = updateCrc(crc, byte);
            }

            return crc ^ FINAL_XOR_VALUE;
        }

        Crc32() = delete;
        ~Crc32() = delete;
        Crc32(const Crc32 &) = delete;
        Crc32 &operator=(const Crc32 &) = delete;
        Crc32(Crc32 &&) = delete;
        Crc32 &operator=(Crc32 &&) = delete;

    private:
        static constexpr std::uint32_t INITIAL_REMAINDER = 0xFFFFFFFFU;
        static constexpr std::uint32_t FINAL_XOR_VALUE = 0xFFFFFFFFU;
        static constexpr std::uint32_t POLYNOMIAL = 0xEDB88320U;
        static constexpr std::uint8_t BITS_PER_BYTE = 8U;
        static constexpr std::uint32_t LSB_MASK = 1U;

        /**
         * @brief Processes a single byte to update the CRC remainder.
         */
        [[nodiscard]] static constexpr std::uint32_t updateCrc(
            const std::uint32_t crc,
            const std::uint8_t byte) noexcept
        {
            std::uint32_t result = crc ^ static_cast<std::uint32_t>(byte);

            for (std::uint8_t i = 0U; i < BITS_PER_BYTE; ++i)
            {
                const bool isLsbSet = (result & LSB_MASK) != 0U;
                result >>= 1U;
                if (isLsbSet)
                {
                    result ^= POLYNOMIAL;
                }
            }

            return result;
        }
    };
}