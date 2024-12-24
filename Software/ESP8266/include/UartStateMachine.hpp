#ifndef UartStateMachine_h
#define UartStateMachine_h

// #include <HardwareSerial.h>
// #include <HardwareSerial.h>

#include "ISerialInterface.hpp"

#include <array>
#include <chrono>
#include <cstdint>
#include <optional>
#include <functional> // for std::reference_wrapper

namespace Device
{
    class UartStateMachine
    {
    public:
        enum class StateMachineState : std::uint8_t
        {
            Inactive = 0,
            Idle = 1,      ///< Ready to receive
            Receiving = 2, ///< Collecting bytes
            Decoding = 3,  ///< Decoding COBS data
            Verifying = 4, ///< Checking length and CRC
            Complete = 5,  ///< Successfully received packet
            Fault = 6      ///< Reception encountered a fault (see RxSubstatus)
        };

        enum class RxStatus : std::uint8_t
        {
            Inactive = 0,
            Active = 1,  ///< Receiving is ongoing
            Finished = 2 ///< Reception cycle ended (success or other outcome — see RxSubstatus)
        };

        enum class RxSubstatus : std::uint8_t
        {
            Ok = 1,             ///< Packet successfully received
            NoData = 2,         ///< No data yet, not an error
            Timeout = 3,        ///< Timeout occurred
            CobsDecodeFail = 4, ///< COBS decode error
            LengthMismatch = 5, ///< Frame length mismatch
            CrcMismatch = 6,    ///< CRC failure
            Overflow = 7,       ///< Buffer overflow
            NoRxBuffer = 8,
            UnknownError = 9 ///< Fallback error
        };

    public:
        //   explicit UartStateMachine(HardwareSerial &device);
        explicit UartStateMachine(ISerialInterface &serial) : deviceHandler(serial) {}

        ~UartStateMachine() = default;

        UartStateMachine(const UartStateMachine &) = delete;
        UartStateMachine &operator=(const UartStateMachine &) = delete;
        UartStateMachine(UartStateMachine &&) = delete;
        UartStateMachine &operator=(UartStateMachine &&) = delete;

        bool open(std::uint32_t baudRate);
        bool close();

        template <std::size_t N>
        void setRxBuffer(std::array<std::uint8_t, N> &buffer)
        {
            static_assert(N == MaxRxSize, "setRxBuffer expects an std::array of size 128");
            rxBufferRef = buffer; // store reference_wrapper
            rxWriteIndex = 0;
        }

        void tick();

        StateMachineState getState() const;
        RxStatus getRxStatus() const;
        RxSubstatus getRxSubstatus() const;

        static constexpr std::size_t MaxRxSize = 128;

    private:
        using ByteArray = std::array<std::uint8_t, MaxRxSize>;
        using ByteArrayRef = std::reference_wrapper<ByteArray>;
        using OptionalByteArrayRef = std::optional<ByteArrayRef>;

        void doDecoding();
        void doVerifying();

        OptionalByteArrayRef rxBufferRef = std::nullopt;
        std::size_t rxWriteIndex = 0;

        RxStatus rxStatus = RxStatus::Inactive;
        RxSubstatus rxSubstatus = RxSubstatus::NoData;

        ISerialInterface &deviceHandler;
        StateMachineState state = StateMachineState::Inactive;
    };

} // namespace Device

#endif
