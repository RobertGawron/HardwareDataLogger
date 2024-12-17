/**
 * @file UartDriver.hpp
 * @brief Defines the UartDriver class for UART communication using STM32 HAL.
 */

#ifndef UartDriver_h
#define UartDriver_h

#include "Driver/Interfaces/IUartDriver.hpp"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

namespace Driver
{
    /**
     * @class UartDriver
     * @brief Implementation of UART communication using STM32 HAL.
     *
     * This class implements the `IUartDriver` interface to handle UART communication
     * using the STM32 HAL library. It provides methods for initializing the UART peripheral,
     * transmitting and receiving data, and additional methods for handling driver state transitions.
     */
    class UartDriver : public IUartDriver
    {
    public:
        /**
         * @brief Constructs a UartDriver with a specified UART handle.
         *
         * Initializes the UartDriver with a reference to a UART handle provided by STM32 HAL.
         *
         * @param uartHandler A reference to the UART handle (`UART_HandleTypeDef`) used by STM32 HAL.
         */
        explicit UartDriver(UART_HandleTypeDef &uartHandler);

        /**
         * @brief Deleted default constructor.
         *
         * Prevents the creation of a UartDriver instance without specifying a UART handle.
         */
        UartDriver() = delete;

        /**
         * @brief Virtual destructor for UartDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~UartDriver() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        UartDriver(const UartDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return UartDriver& The assigned object.
         */
        UartDriver &operator=(const UartDriver &) = delete;

        /**
         * @brief Transmits data over UART.
         *
         * Sends a specified amount of data through UART with a timeout period.
         *
         * @param data Pointer to the data buffer to be transmitted.
         * @param size Number of bytes to transmit.
         * @param timeout Timeout period for the transmission, in milliseconds.
         * @return Status of the UART exchange operation (`UartExchangeStatus`).
         */
        UartExchangeStatus transmit(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout) override;

        /**
         * @brief Receives data over UART.
         *
         * Receives a specified amount of data through UART with a timeout period.
         *
         * @param data Pointer to the buffer where received data will be stored.
         * @param size Number of bytes to receive.
         * @param timeout Timeout period for the reception, in milliseconds.
         * @return Status of the UART exchange operation (`UartExchangeStatus`).
         */
        UartExchangeStatus receive(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout) override;

    protected:
        /**
         * @brief Converts HAL status to UartExchangeStatus.
         *
         * Maps the status returned by STM32 HAL functions to a `UartExchangeStatus` value.
         *
         * @param libStatus The status returned by STM32 HAL (`HAL_StatusTypeDef`).
         * @return The corresponding `UartExchangeStatus`.
         */
        static UartExchangeStatus getExchangeStatus(HAL_StatusTypeDef libStatus);

        /**
         * @brief Initializes the UART driver.
         *
         * This method is called to initialize the UART driver, typically setting up the
         * hardware and preparing the driver for operation.
         *
         * @return True if initialization is successful, otherwise false.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the UART driver.
         *
         * This method is called to start the UART driver, allowing it to begin handling
         * data transmission and reception.
         *
         * @return True if the start operation is successful, otherwise false.
         */
        bool onStart() override;

        /**
         * @brief Stops the UART driver.
         *
         * This method is called to stop the UART driver, halting data transmission and reception.
         *
         * @return True if the stop operation is successful, otherwise false.
         */
        bool onStop() override;

        /**
         * @brief Resets the UART driver.
         *
         * This method is called to reset the UART driver, typically reinitializing hardware
         * and clearing any error states.
         *
         * @return True if the reset operation is successful, otherwise false.
         */
        bool onReset() override;

    private:
        /**
         * @brief UART handle from STM32 HAL library.
         *
         * This reference is used to interact with the UART peripheral.
         */
        UART_HandleTypeDef &uartHandler;
    };

}

#endif // UartDriver_h
