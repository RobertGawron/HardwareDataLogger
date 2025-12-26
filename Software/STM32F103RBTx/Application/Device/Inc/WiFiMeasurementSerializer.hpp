#ifndef WiFiMeasurementSerializer_hpp
#define WiFiMeasurementSerializer_hpp

#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/Crc32.hpp"

#include <cstring>
#include <variant>
#include <cstdint>
#include <array>

namespace Device
{
    namespace CRC_CONSTANTS
    {
        static constexpr std::uint8_t BITS_24 = 24U;
        static constexpr std::uint8_t BITS_16 = 16U;
        static constexpr std::uint8_t BITS_8 = 8U;
        static constexpr std::uint8_t BYTE_MASK = 0xFFU;
    }

    class WiFiMeasurementSerializer
    {
    public:
        static constexpr std::size_t HEADER_LENGTH = 0U;
        static constexpr std::size_t CRC_FIELD_SIZE = 4U;
        static constexpr std::size_t LENGTH_FIELD_SIZE = 2U;

        template <std::size_t BUFFER_SIZE>
        static bool generate(
            const MeasurementType &measurement,
            std::array<std::uint8_t, BUFFER_SIZE> &data,
            std::size_t &totalMsgLength)
        {
            bool result = true;
            totalMsgLength = 0;

            std::size_t neededSize = std::visit(
                [&](auto &&value) -> std::size_t
                {
                    return measurementSize(value); // Now visible to compiler
                },
                measurement.data);

            if (neededSize + HEADER_LENGTH + CRC_FIELD_SIZE > BUFFER_SIZE)
            {
                result = false;
            }
            else
            {
                totalMsgLength = LENGTH_FIELD_SIZE;

                if (totalMsgLength < BUFFER_SIZE)
                {
                    data[totalMsgLength++] = static_cast<std::uint8_t>(measurement.source);
                }
                else
                {
                    result = false;
                }

                std::size_t writtenData = 0;
                if (result)
                {
                    std::visit(
                        [&](auto &&value)
                        {
                            // Now visible to compiler
                            result = appendMeasurement(&data[totalMsgLength], (BUFFER_SIZE - totalMsgLength), writtenData, value);
                        },
                        measurement.data);
                }

                if (result)
                {
                    totalMsgLength += writtenData;

                    if (totalMsgLength + CRC_FIELD_SIZE <= BUFFER_SIZE)
                    {
                        const std::uint32_t crcCalc = Crc32::compute(data, totalMsgLength);

                        data[totalMsgLength++] = static_cast<std::uint8_t>((crcCalc >> CRC_CONSTANTS::BITS_24) & CRC_CONSTANTS::BYTE_MASK);
                        data[totalMsgLength++] = static_cast<std::uint8_t>((crcCalc >> CRC_CONSTANTS::BITS_16) & CRC_CONSTANTS::BYTE_MASK);
                        data[totalMsgLength++] = static_cast<std::uint8_t>((crcCalc >> CRC_CONSTANTS::BITS_8) & CRC_CONSTANTS::BYTE_MASK);
                        data[totalMsgLength++] = static_cast<std::uint8_t>(crcCalc & CRC_CONSTANTS::BYTE_MASK);
                    }
                    else
                    {
                        result = false;
                    }

                    if (totalMsgLength + LENGTH_FIELD_SIZE <= BUFFER_SIZE)
                    {
                        data[0] = static_cast<std::uint8_t>((totalMsgLength >> CRC_CONSTANTS::BITS_8) & CRC_CONSTANTS::BYTE_MASK);
                        data[1] = static_cast<std::uint8_t>(totalMsgLength & CRC_CONSTANTS::BYTE_MASK);
                    }
                    else
                    {
                        result = false;
                    }
                }
            }
            return result;
        }

    private:
        /**
         * @brief Must be a template in the header to be used by the 'generate' template.
         */
        template <typename T>
        static std::size_t measurementSize(const T &value)
        {
            return sizeof(T);
        }

        /**
         * @brief Must be a template in the header to be used by the 'generate' template.
         */
        template <typename T>
        static bool appendMeasurement(std::uint8_t *ptr, std::size_t size, std::size_t &written, const T &value)
        {
            bool result = false;
            if (size >= sizeof(T))
            {
                std::memcpy(ptr, &value, sizeof(T));
                written = sizeof(T);
                result = true;
            }
            return result;
        }
    };
}

#endif // WiFiMeasurementSerializer_hpp