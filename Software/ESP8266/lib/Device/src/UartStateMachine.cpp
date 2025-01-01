#include "UartStateMachine.hpp"

#include <cstring>

namespace Device
{
    /*
        template <std::size_t MaxPacketSize>
        UartStateMachine<MaxPacketSize>::UartStateMachine(std::chrono::milliseconds timeoutMs)
            : timeout(timeoutMs)
        {
            reset();
        }

        template <std::size_t MaxPacketSize>
        ReceiverState UartStateMachine<MaxPacketSize>::getState() const noexcept
        {
            return state;
        }

        template <std::size_t MaxPacketSize>
        DecodeResult UartStateMachine<MaxPacketSize>::getResult() const noexcept
        {
            return lastResult;
        }

        template <std::size_t MaxPacketSize>
        std::size_t UartStateMachine<MaxPacketSize>::readPacket(std::array<std::uint8_t, MaxPacketSize> &outBuffer)
        {
            if (state == ReceiverState::Complete && lastResult == DecodeResult::Ok)
            {
                std::memcpy(outBuffer.data(), decodedBuffer.data(), decodedLength);
                return decodedLength;
            }
            return 0;
        }

        template <std::size_t MaxPacketSize>
        void UartStateMachine<MaxPacketSize>::reset()
        {
            state = ReceiverState::Idle;
            lastResult = DecodeResult::NoData;
            rawBufferIndex = 0;
            decodedLength = 0;
            lastByteTime = {};
        }

        // Explicit template instantiation
        template class UartStateMachine<256>;
    */
} // namespace Device
