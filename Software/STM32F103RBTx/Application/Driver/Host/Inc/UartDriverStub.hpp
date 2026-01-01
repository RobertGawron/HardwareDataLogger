/**
 * @file UartDriverStub.hpp
 * @brief Defines the UartDriverStub class for UART communication using STM32 HAL.
 */

#ifndef UartDriverStub_h
#define UartDriverStub_h

#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/UartId.hpp"

#include <span>

namespace Driver
{

    class UartDriverStub : public IUartDriver
    {
    public:
        UartDriverStub() = delete;

        explicit UartDriverStub(Driver::UartId deviceId);

        /**
         * @brief Virtual destructor for UartDriverStub.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~UartDriverStub() override = default;

        // Deleted copy constructor and assignment operator
        UartDriverStub(const UartDriverStub &) = delete;
        UartDriverStub &operator=(const UartDriverStub &) = delete;

        UartStatus transmit(std::span<const std::uint8_t> data, std::uint32_t timeout) override;

        UartStatus receive(std::span<std::uint8_t> data, std::uint32_t timeout) override;

    protected:
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
        Driver::UartId uartId;
    };

}

#endif // UartDriverStub_h
