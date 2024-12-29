

#ifndef UartDataLinkLayer_hpp
#define UartDataLinkLayer_hpp

#include "Device/Inc/CobsEncoder.hpp"
#include "Device/Inc/Crc32.hpp"
#include <array>
#include <cstring>
#include <variant>
#include <cstdio>

namespace Device
{
    // We have buffer in only one length so only one instance will be generated.
    template <std::size_t InputBufferSize, std::size_t OutputBufferSize>
    class UartDataLinkLayer
    {
    public:
        static std::size_t msgStart()
        {
            return 2;
        }
        bool generateMessage(
            std::array<std::uint8_t, InputBufferSize> &input,
            std::size_t inLength,
            std::array<std::uint8_t, OutputBufferSize> &output,
            std::size_t outLength)
        {
            // save msg length
            auto scpiSize = inLength - msgStart();
            input[0] = static_cast<std::uint8_t>((scpiSize >> 8) & 0xFF);
            input[1] = static_cast<std::uint8_t>(scpiSize & 0xFF);

            const std::size_t crcLength = msgStart() + inLength;
            std::uint32_t crcCalc = crc.compute(&input[0], crcLength);

            //  Store the CRC in big-endian form
            input[crcLength] = static_cast<std::uint8_t>((crcCalc >> 24) & 0xFF);
            input[crcLength + 1] = static_cast<std::uint8_t>((crcCalc >> 16) & 0xFF);
            input[crcLength + 2] = static_cast<std::uint8_t>((crcCalc >> 8) & 0xFF);
            input[crcLength + 3] = static_cast<std::uint8_t>(crcCalc & 0xFF);

            const std::size_t totalLength = crcLength + 4;

            std::size_t encodedLength = encoder.encode(input.data(),
                                                       crcLength,
                                                       output.data(),
                                                       output.size());
            // return encodedLength; // 0 => error, otherwise number of encoded bytes

            return true;
        }
        CobsEncoder encoder;
        Crc32 crc;
    };
}

#endif // UartDataLinkLayer_hpp
