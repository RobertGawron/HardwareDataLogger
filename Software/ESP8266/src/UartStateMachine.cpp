#if 0

#include "UartStateMachine.hpp"
#include "CobsEncoder.hpp"
#include "Crc32.hpp"

#include <cstdint>
#include <cstring>

#include <stdio.h>
namespace Device
{
    bool UartStateMachine::open(std::uint32_t baudRate)
    {
        deviceHandler.begin(baudRate);

        state = StateMachineState::Idle;
        rxStatus = RxStatus::Active;
        rxSubstatus = RxSubstatus::Ok;
        return true;
    }

    bool UartStateMachine::close()
    {
        deviceHandler.end();

        state = StateMachineState::Inactive;
        rxStatus = RxStatus::Inactive;
        rxSubstatus = RxSubstatus::NoData;
        return true;
    }

    void UartStateMachine::tick()
    {
        const uint8_t CobsDelimiter = 0;

        if (state == StateMachineState::Inactive || state == StateMachineState::Fault)
            return;

        if (!rxBufferRef.has_value())
        {
            state = StateMachineState::Fault;
            rxStatus = RxStatus::Inactive;
            rxSubstatus = RxSubstatus::NoRxBuffer;
            return;
        }

        auto &rxBuffer = rxBufferRef->get();

        switch (state)
        {
        case StateMachineState::Decoding:
            doDecoding();
            return;
        case StateMachineState::Verifying:
            doVerifying();
            return;
        case StateMachineState::Complete:
            return;
        case StateMachineState::Idle:
        case StateMachineState::Receiving:
        {

            // Handle byte reading
            int bytesAvailable = deviceHandler.available();
            if (bytesAvailable <= 0)
                return;

            for (int i = 0; i < bytesAvailable; ++i)
            {
                if (rxWriteIndex >= MaxRxSize)
                {
                    state = StateMachineState::Fault;
                    rxStatus = RxStatus::Finished;
                    rxSubstatus = RxSubstatus::Overflow;
                    break;
                }

                std::uint8_t byte = static_cast<std::uint8_t>(deviceHandler.read());

                // Remove file writing for production - only for debugging
                FILE *fptr = fopen("/tmp/filename.txt", "a+");
                fprintf(fptr, "b %d %d\n", byte, bytesAvailable);
                fclose(fptr);

                // Handle state transitions
                if (state == StateMachineState::Idle && byte != CobsDelimiter)
                {
                    // First byte of new packet
                    state = StateMachineState::Receiving;
                    rxStatus = RxStatus::Active;
                    rxSubstatus = RxSubstatus::Ok;
                    rxBuffer[rxWriteIndex++] = byte;
                }
                else if (state == StateMachineState::Receiving)
                {
                    if (byte == CobsDelimiter)
                    {
                        // End of packet - store delimiter and start decoding
                        rxBuffer[rxWriteIndex++] = byte;
                        state = StateMachineState::Decoding;
                        break; // Stop processing more bytes this tick
                    }
                    else
                    {
                        // Regular data byte
                        rxBuffer[rxWriteIndex++] = byte;
                    }
                }
                // Else: ignore unexpected delimiter in Idle state
            }
        }
        break;

        default:
            return;
        }
    }

    void UartStateMachine::doDecoding()
    {
        if (!rxBufferRef.has_value())
        {
            // No buffer available to decode
            state = StateMachineState::Fault;
            rxStatus = RxStatus::Finished;
            rxSubstatus = RxSubstatus::NoRxBuffer;
            return;
        }

        FILE *fptr = fopen("/tmp/filename.txt", "w");
        for (auto i = 0; i < rxWriteIndex; i++)
            // Write some text to the file
            fprintf(fptr, "doDecoding %d\n", rxBufferRef->get()[i]);

        // Close the file
        fclose(fptr);

        // Get the reference to the buffer
        auto &rxBuffer = rxBufferRef->get();

        // Call the COBS decoder - use .data() to get the raw pointer
        std::size_t decodedSize = CobsEncoder::decode(rxBuffer.data(), rxWriteIndex);

        // Check if decoding was successful
        if (decodedSize == 0)
        {
            // Decoding failed
            state = StateMachineState::Fault;
            rxStatus = RxStatus::Finished;
            rxSubstatus = RxSubstatus::CobsDecodeFail;
            return;
        }

        // Successfully decoded data, update rxWriteIndex
        rxWriteIndex = decodedSize;

        // Transition to Verifying state to check length and CRC
        state = StateMachineState::Verifying;
        rxStatus = RxStatus::Active;
        rxSubstatus = RxSubstatus::Ok;
    }

    void UartStateMachine::doVerifying()
    {
        auto &rxBuffer = rxBufferRef->get();

        if (rxWriteIndex < 6)
        {
            state = StateMachineState::Fault;
            rxStatus = RxStatus::Finished;
            rxSubstatus = RxSubstatus::LengthMismatch;
            return;
        }

        std::uint16_t dataLen = (static_cast<std::uint16_t>(rxBuffer[1]) << 8) |
                                static_cast<std::uint16_t>(rxBuffer[0]);

        std::size_t expectedTotal = 2 + dataLen + 4;
        if (expectedTotal != rxWriteIndex)
        {
            state = StateMachineState::Fault;
            rxStatus = RxStatus::Finished;
            rxSubstatus = RxSubstatus::LengthMismatch;
            return;
        }

        std::size_t crcOffset = 2 + dataLen;
        std::uint32_t packetCrc =
            (static_cast<std::uint32_t>(rxBuffer[crcOffset + 0]) << 0) |
            (static_cast<std::uint32_t>(rxBuffer[crcOffset + 1]) << 8) |
            (static_cast<std::uint32_t>(rxBuffer[crcOffset + 2]) << 16) |
            (static_cast<std::uint32_t>(rxBuffer[crcOffset + 3]) << 24);

        std::uint32_t computedCrc = Crc32::compute(&rxBuffer[2], dataLen);

        if (computedCrc != packetCrc)
        {
            state = StateMachineState::Fault;
            rxStatus = RxStatus::Finished;
            rxSubstatus = RxSubstatus::CrcMismatch;
            return;
        }

        state = StateMachineState::Complete;
        rxStatus = RxStatus::Finished;
        rxSubstatus = RxSubstatus::Ok;
    }

    UartStateMachine::StateMachineState UartStateMachine::getState() const
    {
        return state;
    }

    UartStateMachine::RxStatus UartStateMachine::getRxStatus() const
    {
        return rxStatus;
    }

    UartStateMachine::RxSubstatus UartStateMachine::getRxSubstatus() const
    {
        return rxSubstatus;
    }

} // namespace Device


#endif