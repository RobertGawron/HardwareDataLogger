/**
 * @file UartMeasurementRecorder.hpp
 * @brief Defines the UartMeasurementRecorder class responsible for sending measurement data
 *        to a COM port via UART over USB.
 */

#ifndef UartMeasurementRecorder_H_
#define UartMeasurementRecorder_H_

#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

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
    class UartMeasurementRecorder : public IMeasurementRecorder
    {
    public:
        /**
         * @brief Constructs a UartMeasurementRecorder with a reference to a UART driver.
         *
         * @param driver Reference to the UART driver responsible for managing UART communication.
         */
        explicit UartMeasurementRecorder(Driver::IUartDriver &driver);

        /**
         * @brief Default destructor for UartMeasurementRecorder.
         */
        virtual ~UartMeasurementRecorder() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        UartMeasurementRecorder(const UartMeasurementRecorder &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return UartMeasurementRecorder& The assigned object.
         */
        UartMeasurementRecorder &operator=(const UartMeasurementRecorder &) = delete;

        /**
         * @brief Writes measurement data to the COM port via UART.
         *
         * This method writes the prepared measurement data to the COM port using the UART driver.
         */
        virtual void write() override;

        /**
         * @brief Flushes any remaining data to the COM port via UART.
         *
         * This method ensures that any remaining buffered data is sent to the COM port via UART.
         */
        virtual void flush() override;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available
         * and should be sent to the COM port via UART.
         */
        virtual void notify() override;

    protected:
        /**
         * @brief Initializes the UartMeasurementRecorder.
         *
         * This method is responsible for initializing the recorder and preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        virtual bool onInitialize() override;

        /**
         * @brief Starts the UartMeasurementRecorder.
         *
         * This method starts the recorder, enabling it to begin sending measurement data to the COM port via UART.
         * @return True if the recorder started successfully, false otherwise.
         */
        virtual bool onStart() override;

        /**
         * @brief Stops the UartMeasurementRecorder.
         *
         * This method stops the recorder, halting any further transmission of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        virtual bool onStop() override;

        /**
         * @brief Resets the UartMeasurementRecorder.
         *
         * This method resets the recorder, clearing any internal state or buffers.
         * @return True if the recorder was reset successfully, false otherwise.
         */
        virtual bool onReset() override;

    private:
        /** @brief Reference to the UART driver used for communication with the COM port. */
        Driver::IUartDriver &driver;
    };

}

#endif // UartMeasurementRecorder_H_