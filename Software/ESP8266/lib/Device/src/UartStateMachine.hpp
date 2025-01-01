#pragma once

#include <HardwareSerial.h>

#include "CobsEncoder.hpp"
#include "Crc32.hpp"

#include <cstdint>
#include <array>
#include <chrono>
#include <optional>

namespace Device
{

    /**
     * @brief Possible outcomes when we finish receiving/decoding a packet
     */
    enum class DecodeResult : std::uint8_t
    {
        Ok,             ///< Packet was successfully received and decoded
        Timeout,        ///< Timed out waiting for completion
        CobsDecodeFail, ///< COBS decode error
        LengthMismatch, ///< Decoded length field doesn't match actual bytes
        CrcMismatch,    ///< CRC check failed
        NoData          ///< No data has arrived yet (not really an error)
    };

    /**
     * @brief States for our small packet receiver
     */
    enum class ReceiverState : std::uint8_t
    {
        Idle,      ///< Not currently processing a packet
        Receiving, ///< Gathering bytes from UART
        Decoding,  ///< We have an entire raw frame, now decode it
        Verifying, ///< Validate length, CRC, etc.
        Complete,  ///< Packet is good; user can read the result
        Error      ///< Some error occurred; state machine will reset
    };

    //  template <std::size_t MaxPacketSize = 256>
    class UartStateMachine
    {
    public:
        static constexpr std::size_t LengthFieldSize = 2;
        static constexpr std::size_t CrcFieldSize = 4;
        static constexpr std::size_t HeaderLength = LengthFieldSize;

        HardwareSerial &serialHandler; // from "HardwareSerial.h"
        std::uint32_t baudRate;
        //  std::chrono::milliseconds timeoutMs;

        explicit UartStateMachine(
            HardwareSerial &serialHandler, // from "HardwareSerial.h"
            std::uint32_t baudRate         /*,
                     std::chrono::milliseconds timeoutMs*/
            )
            : serialHandler(serialHandler),
              baudRate(baudRate) //,
        //  timeoutMs(timeoutMs)
        {
        }

        bool open()
        {
            Serial.begin(baudRate);

            // 'begin" method is type of void
            return true;
        }

        template <std::size_t MaxLength>
        bool send(const std::array<std::uint8_t, MaxLength> &data,
                  std::size_t size,
                  std::chrono::milliseconds timeout)
        {
            return true;
        }
        // bool send()
        /*
                /// ====

                template <typename TimePoint, typename ReadByteFn>
                void update(const TimePoint &now, ReadByteFn readByteFunc);

                ReceiverState getState() const noexcept;
                DecodeResult getResult() const noexcept;

                std::size_t readPacket(std::array<std::uint8_t, MaxPacketSize> &outBuffer);
                void reset();

            private:
                template <typename ReadByteFn, typename TimePoint>
                void processIdle(ReadByteFn readByteFunc, const TimePoint &now);

                template <typename ReadByteFn, typename TimePoint>
                void processReceiving(ReadByteFn readByteFunc, const TimePoint &now);

                void processDecoding();
                void processVerifying();

                ReceiverState state = ReceiverState::Idle;
                DecodeResult lastResult = DecodeResult::NoData;

                std::chrono::milliseconds timeout;
                std::chrono::steady_clock::time_point lastByteTime{};

                std::array<uint8_t, MaxPacketSize> rawBuffer{};
                std::size_t rawBufferIndex = 0;

                std::array<uint8_t, MaxPacketSize> decodedBuffer{};
                std::size_t decodedLength = 0;
                */
    };

} // namespace Device
