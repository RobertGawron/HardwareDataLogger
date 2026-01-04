module;

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <expected>
#include <span>
#include <type_traits>
#include <variant>

export module Device.WiFiSerializer;

import Device.MeasurementType;
import Device.Crc32;

export namespace Device
{
    enum class SerializationError : std::uint8_t
    {
        BufferTooSmall,
        InvalidMeasurement
    };

    class WiFiSerializer final
    {
    public:
        /**
         * @brief Serializes a measurement into the provided buffer.
         * Format: [Length (2, LE)][SourceID (1)][Value (N, LE)][CRC (4, LE)]
         *
         * All multi-byte values are serialized in Little Endian for STM32/ESP32 compatibility.
         *
         * @param measurement Input data.
         * @param output Output buffer span.
         * @return Number of bytes written, or error.
         */
        [[nodiscard]] static constexpr std::expected<std::size_t, SerializationError> serialize(
            const MeasurementType &measurement,
            std::span<std::uint8_t> output) noexcept
        {
            const std::size_t valueSize = std::visit([]<typename T>(const T &) constexpr noexcept
                                                     { return sizeof(T); }, measurement.data);

            const std::size_t requiredSize = PROTOCOL_OVERHEAD + valueSize;

            if (requiredSize > output.size()) [[unlikely]]
            {
                return std::unexpected(SerializationError::BufferTooSmall);
            }

            std::size_t cursor{0};

            writeLittleEndian(static_cast<std::uint16_t>(requiredSize), output, cursor);
            output[cursor++] = static_cast<std::uint8_t>(measurement.source);

            std::visit([&]<typename T>(const T &val) constexpr noexcept
                       { writeLittleEndian(val, output, cursor); }, measurement.data);

            const std::uint32_t crcCalc = Crc32::compute(output.subspan(0, cursor));
            writeLittleEndian(crcCalc, output, cursor);

            return cursor;
        }

        /**
         * @brief Calculates the exact serialized size for a measurement.
         */
        [[nodiscard]] static constexpr std::size_t getSerializedSize(
            const MeasurementType &measurement) noexcept
        {
            const std::size_t valueSize = std::visit([]<typename T>(const T &) constexpr noexcept
                                                     { return sizeof(T); }, measurement.data);

            return PROTOCOL_OVERHEAD + valueSize;
        }

        /**
         * @brief Calculates the maximum possible serialized size at compile-time.
         */
        [[nodiscard]] static consteval std::size_t getMaxSerializedSize() noexcept
        {
            return PROTOCOL_OVERHEAD + getMaxVariantSize<MeasurementType::DataVariant>();
        }

        WiFiSerializer() = delete;
        ~WiFiSerializer() = delete;
        WiFiSerializer(const WiFiSerializer &) = delete;
        WiFiSerializer &operator=(const WiFiSerializer &) = delete;
        WiFiSerializer(WiFiSerializer &&) = delete;
        WiFiSerializer &operator=(WiFiSerializer &&) = delete;

    private:
        static constexpr std::size_t FIELD_LEN_SIZE{2};
        static constexpr std::size_t FIELD_SRC_SIZE{1};
        static constexpr std::size_t FIELD_CRC_SIZE{4};
        static constexpr std::size_t PROTOCOL_OVERHEAD{FIELD_LEN_SIZE + FIELD_SRC_SIZE + FIELD_CRC_SIZE};

        static constexpr std::uint8_t BITS_PER_BYTE{8};
        static constexpr std::uint8_t BYTE_MASK{0xFF};

        static constexpr std::size_t SIZE_BYTE{1};
        static constexpr std::size_t SIZE_WORD{2};
        static constexpr std::size_t SIZE_DWORD{4};
        static constexpr std::size_t SIZE_QWORD{8};

        template <typename Variant>
        [[nodiscard]] static consteval std::size_t getMaxVariantSize() noexcept
        {
            return []<std::size_t... Is>(std::index_sequence<Is...>) consteval noexcept
            {
                return std::max({sizeof(std::variant_alternative_t<Is, Variant>)...});
            }(std::make_index_sequence<std::variant_size_v<Variant>>{});
        }

        template <typename T>
        static bool writeLittleEndian(
            const T &value,
            std::span<std::uint8_t> output,
            std::size_t &cursor) noexcept
        {
            static_assert(std::is_trivially_copyable_v<T>);
            static_assert(std::endian::native == std::endian::little,
                          "Optimized path requires Little Endian hardware");

            // Evaluate success condition
            const bool success = (cursor + sizeof(T) <= output.size());

            // Perform operation if valid
            if (success) [[likely]]
            {
                // On STM32, this optimizes to a single 'str' (store) instruction
                // regardless of the boolean flag wrapping it.
                std::memcpy(output.data() + cursor, &value, sizeof(T));
                cursor += sizeof(T);
            }

            return success;
        }
    };

} // namespace Device