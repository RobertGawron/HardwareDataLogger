#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Crc32.hpp"

#include <cstring>
#include <variant>
#include <cstdint>

namespace Device
{
    namespace CrcConstants
    {
        constexpr std::uint8_t BITS_24 = 24;
        constexpr std::uint8_t BITS_16 = 16;
        constexpr std::uint8_t BITS_8 = 8;
        constexpr std::uint8_t BYTE_MASK = 0xFF;
    }

    bool WiFiMeasurementSerializer::generate(
        const MeasurementType &measurement,
        std::uint8_t *data,
        std::size_t bufferSize,
        std::size_t &totalMsgLength)
    {
        bool result = true;
        totalMsgLength = 0;

        // Calculate needed size for the measurement
        std::size_t neededSize = std::visit(
            [&](auto &&value) -> std::size_t
            {
                return measurementSize(value);
            },
            measurement.data);

        // Ensure that the buffer is large enough for the data
        if (neededSize + HeaderLength + CrcFieldSize > bufferSize)
        {
            result = false;
        }
        else
        {
            // Reserve space for length field (2 bytes)
            totalMsgLength = LengthFieldSize;

            // Write source byte to the buffer
            if (totalMsgLength < bufferSize)
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
                // Append the measurement data
                std::visit(
                    [&](auto &&value)
                    {
                        result = appendMeasurement(&data[totalMsgLength], (bufferSize - totalMsgLength), writtenData, value);
                    },
                    measurement.data);
            }

            if (result)
            {
                totalMsgLength += writtenData;

                // Ensure we have space for CRC (4 bytes)
                if (totalMsgLength + CrcFieldSize <= bufferSize)
                {
                    // Calculate CRC and append to the buffer
                    const std::uint32_t crcCalc = Crc32::compute(data, totalMsgLength);

                    data[totalMsgLength++] = static_cast<std::uint8_t>((crcCalc >> CrcConstants::BITS_24) & CrcConstants::BYTE_MASK);
                    data[totalMsgLength++] = static_cast<std::uint8_t>((crcCalc >> CrcConstants::BITS_16) & CrcConstants::BYTE_MASK);
                    data[totalMsgLength++] = static_cast<std::uint8_t>((crcCalc >> CrcConstants::BITS_8) & CrcConstants::BYTE_MASK);
                    data[totalMsgLength++] = static_cast<std::uint8_t>(crcCalc & CrcConstants::BYTE_MASK);
                }
                else
                {
                    result = false;
                }

                // Ensure we have space to write the length field at the beginning (2 bytes)
                if (totalMsgLength + LengthFieldSize <= bufferSize)
                {
                    data[0] = static_cast<std::uint8_t>((totalMsgLength >> CrcConstants::BITS_8) & CrcConstants::BYTE_MASK);
                    data[1] = static_cast<std::uint8_t>(totalMsgLength & CrcConstants::BYTE_MASK);
                }
                else
                {
                    result = false;
                }
            }
        }

        return result;
    }
}
