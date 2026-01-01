/**
 * @file UartMeasurementRecorder.hpp
 * @brief Defines the UartMeasurementRecorder class responsible for sending measurement data
 *        to a COM port via UART over USB.
 */

#ifndef UART_MEASUREMENT_RECORDER_HPP
#define UART_MEASUREMENT_RECORDER_HPP

#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Driver/Interface/IUartDriver.hpp"

namespace Device
{
    /**
     * @class UartMeasurementRecorder
     * @brief Handles sending measurement data to a computer's COM port via UART over USB.
     *
     * The UartMeasurementRecorder class interacts with a UART driver to send measurement data
     * over a COM port, typically using UART over USB. It provides methods to manage the
     * initialization, transmission, and lifecycle of the data recording process.
     */
    class UartMeasurementRecorder final : public IMeasurementRecorder
    {
    public:
        /**
         * @brief Constructs a UartMeasurementRecorder with a reference to a UART driver.
         *
         * @param driver Reference to the UART driver responsible for managing UART communication.
         */
        explicit constexpr UartMeasurementRecorder(Driver::IUartDriver &driver) noexcept
            : driver{driver}
        {
        }

        /**
         * @brief Default destructor for UartMeasurementRecorder.
         */
        ~UartMeasurementRecorder() override = default;

        // Non-copyable and non-movable
        UartMeasurementRecorder(const UartMeasurementRecorder &) = delete;
        UartMeasurementRecorder(UartMeasurementRecorder &&) = delete;
        UartMeasurementRecorder &operator=(const UartMeasurementRecorder &) = delete;
        UartMeasurementRecorder &operator=(UartMeasurementRecorder &&) = delete;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available
         * and should be sent to the COM port via UART.
         */
        [[nodiscard]] bool notify(const MeasurementType &measurement) noexcept override;

    protected:
        /**
         * @brief Initializes the UartMeasurementRecorder.
         *
         * This method is responsible for initializing the recorder and preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        [[nodiscard]] bool onInitialize() noexcept override;

        /**
         * @brief Starts the UartMeasurementRecorder.
         *
         * This method starts the recorder, enabling it to begin sending measurement data to the COM port via UART.
         * @return True if the recorder started successfully, false otherwise.
         */
        [[nodiscard]] bool onStart() noexcept override;

        /**
         * @brief Stops the UartMeasurementRecorder.
         *
         * This method stops the recorder, halting any further transmission of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        [[nodiscard]] bool onStop() noexcept override;

        /**
         * @brief Resets the UartMeasurementRecorder.
         *
         * This method resets the recorder, clearing any internal state or buffers.
         * @return True if the recorder was reset successfully, false otherwise.
         */
        [[nodiscard]] bool onReset() noexcept override;

    private:
        Driver::IUartDriver &driver;
    };

} // namespace Device

#endif // UART_MEASUREMENT_RECORDER_HPP