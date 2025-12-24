/**
 * @file IUartDriver.hpp
 * @brief Defines the IUartDriver interface for UART communication.
 */

#ifndef IUartDriver_h
#define IUartDriver_h

#include "Driver/Interfaces/UartExchangeStatus.hpp"
#include "Driver/Interfaces/DriverState.hpp"
#include <cstdint>

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

        /**
         * @brief Transmits data over UART.
         *
         * This function sends a specified amount of data through the UART interface.
         *
         * @param data A pointer to the data to be transmitted.
         * @param size The number of bytes to transmit.
         * @param timeout The maximum time to wait for the transmission to complete, in milliseconds.
         * @return The status of the transmission operation (`UartExchangeStatus`).
         */
        virtual UartExchangeStatus transmit(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout) = 0;

        /**
         * @brief Receives data over UART.
         *
         * This function reads a specified amount of data from the UART interface.
         *
         * @param data A pointer to a buffer where the received data will be stored.
         * @param size The number of bytes to receive.
         * @param timeout The maximum time to wait for the reception to complete, in milliseconds.
         * @return The status of the reception operation (`UartExchangeStatus`).
         */
        virtual UartExchangeStatus receive(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout) = 0;

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
