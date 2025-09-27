#ifndef WIFI_MEASUREMENT_SERIALIZER_HPP
#define WIFI_MEASUREMENT_SERIALIZER_HPP

#include "Device/Inc/MeasurementType.hpp"
#include <cstdint>
#include <cstddef>
#include <variant>
#include <type_traits>

namespace Device
{
    class WiFiMeasurementSerializer
    {
    public:
        bool generate(
            const MeasurementType &measurement,
            std::uint8_t *data,
            std::size_t bufferSize,
            std::size_t &totalMsgLength);

        static constexpr std::size_t LengthFieldSize = 2u;
        static constexpr std::size_t CrcFieldSize = 4u;
        static constexpr std::size_t HeaderLength = LengthFieldSize;

    private:
        template <typename T>
        [[nodiscard]] constexpr std::size_t measurementSize(T value) const
        {
            static_assert(std::is_integral_v<T>, "Only integral types are supported");
            return sizeof(std::uint8_t) + sizeof(T); // 1 byte for source + measurement data
        }

        template <typename T>
        bool appendMeasurement(
            std::uint8_t *data,
            std::size_t bufferSize,
            std::size_t &currentIndex,
            T value)
        {
            static_assert(std::is_integral_v<T>, "appendMeasurement only supports integral types");
            constexpr std::size_t typeSize = sizeof(T);
            bool result = true; // Assume success

            // Ensure there is enough space in the buffer before accessing it
            if ((currentIndex + typeSize) <= bufferSize)
            {
                // Append the measurement value to the data buffer, byte by byte
                for (std::size_t i = 0; i < typeSize; ++i)
                {
                    // Check after incrementing currentIndex to avoid overflow
                    if (currentIndex >= bufferSize)
                    {
                        result = false; // Not enough space, set result to false
                        break;
                    }
                    data[currentIndex++] = static_cast<std::uint8_t>((value >> (i * 8)) & 0xFF);
                }
            }
            else
            {
                result = false; // Not enough space, set result to false
            }

            return result;
        }
    };
}

#endif // WIFI_MEASUREMENT_SERIALIZER_HPP
