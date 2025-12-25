/**
 * @file IUartDriver.hpp
 * @brief Defines the IUartDriver interface for UART communication.
 */

#ifndef IUartDriver_h
#define IUartDriver_h

#include "Driver/Interface/UartStatus.hpp"
#include "Driver/Interface/DriverState.hpp"
#include <cstdint>
#include <span>
namespace Driver
{

    /**
     * @class IUartDriver
     * @brief Interface for UART (Universal Asynchronous Receiver-Transmitter) drivers.
     *
     * This interface provides a set of pure virtual functions that must be implemented
     * by any UART driver. It includes basic operations for initializing the UART, transmitting,
     * and receiving data, along with status reporting.
     */
    class IUartDriver : public DriverState
    {
    public:
        /**
         * @brief Default constructor for IUartDriver.
         */
        IUartDriver() = default;

        /**
         * @brief Virtual destructor for IUartDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IUartDriver() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        IUartDriver(const IUartDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return IUartDriver& The assigned object.
         */
        IUartDriver &operator=(const IUartDriver &) = delete;

        virtual UartStatus transmit(std::span<const std::uint8_t> data, std::uint32_t timeout) = 0;

        virtual UartStatus receive(std::span<std::uint8_t> data, std::uint32_t timeout) = 0;

        /**
         * @brief Maximum possible delay for transmit/receive operations.
         *
         * This constant defines the maximum delay value, in milliseconds, for UART operations.
         * It is typically used to indicate an infinite timeout, where the function will wait
         * indefinitely for the operation to complete.
         */
        static constexpr std::uint32_t MaxDelay{0xFFFFFFFFU};
    };

}

#endif // IUartDriver_h
