#ifndef WiFiMeasurementSerializer_hpp
#define WiFiMeasurementSerializer_hpp

#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/Crc32.hpp"

#include <cstring>
#include <variant>
#include <cstdint>
#include <array>
#include <type_traits>

namespace Device
{
    class WiFiMeasurementSerializer
    {
    private:
        // Protocol Layout Constants
        static constexpr std::size_t FIELD_LEN_SIZE = 2U;
        static constexpr std::size_t FIELD_SRC_SIZE = 1U;
        static constexpr std::size_t FIELD_CRC_SIZE = 4U;

        // Total fixed overhead: Length(2) + Source(1) + CRC(4)
        static constexpr std::size_t PROTOCOL_OVERHEAD = FIELD_LEN_SIZE + FIELD_SRC_SIZE + FIELD_CRC_SIZE;

        // Bitwise Constants
        static constexpr std::uint8_t BITS_PER_BYTE = 8U;
        static constexpr std::uint8_t BITS_24 = 24U;
        static constexpr std::uint8_t BITS_16 = 16U;
        static constexpr std::uint8_t BITS_8 = 8U;
        static constexpr std::uint8_t BYTE_MASK = 0xFFU;

        // Size constants for type checking
        static constexpr std::size_t SIZE_BYTE = 1U;
        static constexpr std::size_t SIZE_WORD = 2U;
        static constexpr std::size_t SIZE_DWORD = 4U;
        static constexpr std::size_t SIZE_QWORD = 8U;

        /**
         * @brief Generic Little Endian serializer for any trivial type.
         * Handles integers, floats, doubles, etc. by reinterpreting as unsigned integer.
         *
         * @tparam T The type to serialize (must be trivially copyable)
         * @tparam N The size of the data array
         * @param value The value to serialize
         * @param data Output buffer array reference
         * @param cursor Current position in buffer (will be advanced)
         */
        template <typename T, std::size_t N>
        static void serializeLittleEndian(const T &value, std::array<std::uint8_t, N> &data, std::size_t &cursor)
        {
            static_assert(std::is_trivially_copyable_v<T>, "Type must be trivially copyable");

            if constexpr (sizeof(T) == SIZE_BYTE)
            {
                // Single byte - no endianness issue
                data[cursor++] = static_cast<std::uint8_t>(value);
            }
            else
            {
                // Multi-byte type - serialize as Little Endian
                // Reinterpret the value as unsigned integer of same size
                using UIntType = std::conditional_t<sizeof(T) == SIZE_WORD, std::uint16_t,
                                                    std::conditional_t<sizeof(T) == SIZE_DWORD, std::uint32_t,
                                                                       std::conditional_t<sizeof(T) == SIZE_QWORD, std::uint64_t, void>>>;

                static_assert(!std::is_same_v<UIntType, void>, "Unsupported type size");

                UIntType temp;
                std::memcpy(&temp, &value, sizeof(T));

                // Write bytes in Little Endian order (LSB first)
                for (std::size_t i = 0U; i < sizeof(T); ++i)
                {
                    data[cursor++] = static_cast<std::uint8_t>((temp >> (i * BITS_PER_BYTE)) & BYTE_MASK);
                }
            }
        }

    public:
        /**
         * @brief Serializes a measurement into the provided buffer.
         * Format: [Length (2, BE)][SourceID (1)][Value (N, LE)][CRC (4, BE)]
         *
         * All multi-byte values (except Length and CRC) are serialized in Little Endian.
         * Length and CRC use Big Endian (network byte order).
         *
         * @tparam BUFFER_SIZE Deduced from the array.
         * @param measurement Input data.
         * @param data Output buffer.
         * @param totalMsgLength Output variable for the actual written size.
         * @return true if serialization succeeded, false if buffer was too small.
         */
        template <std::size_t BUFFER_SIZE>
        [[nodiscard]] static bool generate(
            const MeasurementType &measurement,
            std::array<std::uint8_t, BUFFER_SIZE> &data,
            std::size_t &totalMsgLength)
        {
            bool isSuccessful = false;
            totalMsgLength = 0U;

            // 1. Calculate the size of the variant data
            const std::size_t valueSize = std::visit([](const auto &val)
                                                     { return sizeof(val); },
                                                     measurement.data);

            // 2. Pre-calculate total required size
            const std::size_t requiredSize = PROTOCOL_OVERHEAD + valueSize;

            // 3. Perform Serialization if buffer permits
            if (requiredSize <= BUFFER_SIZE)
            {
                std::size_t cursor = 0U;

                // A. Write Length field (Big Endian) - temporary value, will update after CRC
                const std::uint16_t tempLength = static_cast<std::uint16_t>(requiredSize);
                data[cursor++] = static_cast<std::uint8_t>((tempLength >> BITS_8) & BYTE_MASK);
                data[cursor++] = static_cast<std::uint8_t>(tempLength & BYTE_MASK);

                // B. Write Source ID
                data[cursor++] = static_cast<std::uint8_t>(measurement.source);

                // C. Write Measurement Value (Little Endian)
                std::visit([&](const auto &val)
                           { serializeLittleEndian(val, data, cursor); },
                           measurement.data);

                // D. Calculate CRC over [Length + Source + Data]
                const std::uint32_t crcCalc = Crc32::compute(data, cursor);

                // E. Write CRC (Big Endian)
                data[cursor++] = static_cast<std::uint8_t>((crcCalc >> BITS_24) & BYTE_MASK);
                data[cursor++] = static_cast<std::uint8_t>((crcCalc >> BITS_16) & BYTE_MASK);
                data[cursor++] = static_cast<std::uint8_t>((crcCalc >> BITS_8) & BYTE_MASK);
                data[cursor++] = static_cast<std::uint8_t>(crcCalc & BYTE_MASK);

                totalMsgLength = cursor;
                isSuccessful = true;
            }

            return isSuccessful;
        }
    };
}

#endif // WiFiMeasurementSerializer_hpp
