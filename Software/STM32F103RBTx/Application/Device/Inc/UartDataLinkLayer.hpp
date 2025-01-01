

#ifndef UartDataLinkLayer_hpp
#define UartDataLinkLayer_hpp

#include "CobsEncoder.hpp" // from common lib for ESP andSTM
#include "Crc32.hpp"       // from common lib for ESP andSTM
#include <array>
#include <cstring>
#include <variant>
#include <cstdio>
// #include <iostream>

namespace Device
{
    // We have buffer in only one length so only one instance will be generated.
    template <std::size_t InputBufferSize, std::size_t OutputBufferSize>
    class UartDataLinkLayer
    {
    public:
        static constexpr std::size_t LengthFieldSize = 2u;
        static constexpr std::size_t CrcFieldSize = 4u;
        static constexpr std::size_t HeaderLength = LengthFieldSize;

        static constexpr std::size_t MaxNeededOutputSize =
            InputBufferSize + (InputBufferSize / 254) + 2;

        // Static assertion to validate buffer sizes
        static_assert(OutputBufferSize >= MaxNeededOutputSize,
                      "Output buffer size is insufficient for worst-case COBS encoding.");

        static constexpr bool isMessageLengthValid(std::size_t inLength)
        {
            const bool isNotZero = (inLength > 0u); // we will not send empty messages
            const bool isNotToLong = ((inLength + LengthFieldSize + CrcFieldSize) <= InputBufferSize);

            return (isNotZero && isNotToLong);
        }

        // it ads header where length of data is at the begining and crc with header + message length
        // then in output it encode the message
        bool generate(
            std::array<std::uint8_t, InputBufferSize> &input,
            std::size_t inLength,
            std::array<std::uint8_t, OutputBufferSize> &output,
            std::size_t &outLength)
        {
            bool status = false;

            if (isMessageLengthValid(inLength))
            {

                std::uint8_t totalMsgLen = HeaderLength + inLength;
                input[0] = static_cast<std::uint8_t>((totalMsgLen >> 8) & 0xFF);
                input[1] = static_cast<std::uint8_t>(totalMsgLen & 0xFF);

                std::uint32_t crcCalc = crc.compute(&input[0], totalMsgLen);

                //  Store the CRC in big-endian form
                input[totalMsgLen++] = static_cast<std::uint8_t>((crcCalc >> 24) & 0xFF);
                input[totalMsgLen++] = static_cast<std::uint8_t>((crcCalc >> 16) & 0xFF);
                input[totalMsgLen++] = static_cast<std::uint8_t>((crcCalc >> 8) & 0xFF);
                input[totalMsgLen++] = static_cast<std::uint8_t>(crcCalc & 0xFF);

                outLength = encoder.encode(input.data(),
                                           totalMsgLen,
                                           output.data(),
                                           output.size());

                status = (outLength > 0u);
            }

            return status;
        }

    private:
        CobsEncoder encoder;
        Crc32 crc;
    };
}

#endif // UartDataLinkLayer_hpp
