/**
 * @file UartDriverStub.hpp
 * @brief Defines the UartDriverStub class for UART communication using STM32 HAL.
 */

#ifndef UartDriverStub_h
#define UartDriverStub_h

#include "IUartDriver.hpp"

namespace Driver
{
    /**
     * @class UartDriverStub
     * @brief Implementation of UART communication using STM32 HAL.
     *
     * This class implements the `IUartDriver` interface to handle UART communication
     * using the STM32 HAL library. It provides methods for initializing the UART peripheral,
     * transmitting and receiving data, and additional methods for handling driver state transitions.
     */
    class UartDriverStub : public IUartDriver
    {
    public:
        /**
         * @brief Default constructor.
         *
         */
        UartDriverStub() = default;

        /**
         * @brief Virtual destructor for UartDriverStub.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~UartDriverStub() = default;

        // Deleted copy constructor and assignment operator
        UartDriverStub(const UartDriverStub &) = delete;
        UartDriverStub &operator=(const UartDriverStub &) = delete;

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
        virtual UartExchangeStatus transmit(uint8_t *data, uint16_t size, uint32_t timeout) override;

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
        virtual UartExchangeStatus receive(uint8_t *data, uint16_t size, uint32_t timeout) override;

    protected:
        /**
         * @brief Initializes the UART driver.
         *
         * This method is called to initialize the UART driver, typically setting up the
         * hardware and preparing the driver for operation.
         *
         * @return True if initialization is successful, otherwise false.
         */
        virtual bool onInitialize() override;

        /**
         * @brief Starts the UART driver.
         *
         * This method is called to start the UART driver, allowing it to begin handling
         * data transmission and reception.
         *
         * @return True if the start operation is successful, otherwise false.
         */
        virtual bool onStart() override;

        /**
         * @brief Stops the UART driver.
         *
         * This method is called to stop the UART driver, halting data transmission and reception.
         *
         * @return True if the stop operation is successful, otherwise false.
         */
        virtual bool onStop() override;

        /**
         * @brief Resets the UART driver.
         *
         * This method is called to reset the UART driver, typically reinitializing hardware
         * and clearing any error states.
         *
         * @return True if the reset operation is successful, otherwise false.
         */
        virtual bool onReset() override;
    };

}

#endif // UartDriverStub_h