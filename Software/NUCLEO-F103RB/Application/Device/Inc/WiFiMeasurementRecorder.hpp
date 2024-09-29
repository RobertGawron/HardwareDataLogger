/**
 * @file WiFiMeasurementRecorder.hpp
 * @brief Defines the WiFiMeasurementRecorder class responsible for sending measurement data
 *        to an ESP module via UART, which then sends the data over WiFi.
 */

#ifndef WiFiMeasurementRecorder_H_
#define WiFiMeasurementRecorder_H_

#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

namespace Device
{
    /**
     * @class WiFiMeasurementRecorder
     * @brief Responsible for sending data to an ESP module, which forwards it via WiFi.
     *
     * Despite its name, the WiFiMeasurementRecorder class uses UART to communicate with the ESP module.
     * The ESP module, in turn, sends the data over WiFi. The class handles the transmission of measurement
     * data via UART but does not handle the WiFi network name or password, which are managed by the ESP module.
     */
    class WiFiMeasurementRecorder : public IMeasurementRecorder
    {
    public:
              /**
         * @brief Constructs a WiFiMeasurementRecorder with a reference to a UART driver.
         *
         * @param driver Reference to the UART driver used to communicate with the ESP module.
         */
        explicit WiFiMeasurementRecorder(Driver::IUartDriver &driver);

        /**
         * @brief Deleted default constructor to prevent instantiation without a driver.
         */
        WiFiMeasurementRecorder() = delete;

        /**
         * @brief Default destructor for WiFiMeasurementRecorder.
         */
        virtual ~WiFiMeasurementRecorder() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        WiFiMeasurementRecorder(const WiFiMeasurementRecorder &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return WiFiMeasurementRecorder& The assigned object.
         */
        WiFiMeasurementRecorder &operator=(const WiFiMeasurementRecorder &) = delete;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available and
         * should be sent to the ESP module via UART.
         */
        virtual void notify() override;

    protected:
        /**
         * @brief Initializes the WiFiMeasurementRecorder.
         *
         * This method is responsible for initializing the recorder, preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        virtual bool onInitialize() override;

        /**
         * @brief Starts the WiFiMeasurementRecorder.
         *
         * This method starts the recorder, enabling it to begin sending measurement data via UART.
         * @return True if the recorder started successfully, false otherwise.
         */
        virtual bool onStart() override;

        /**
         * @brief Stops the WiFiMeasurementRecorder.
         *
         * This method stops the recorder, halting any further transmission of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        virtual bool onStop() override;

        /**
         * @brief Resets the WiFiMeasurementRecorder.
         *
         * This method resets the recorder, clearing any internal state or buffers.
         * @return True if the recorder was reset successfully, false otherwise.
         */
        virtual bool onReset() override;

        /**
         * @brief Writes the measurement data to the ESP module via UART.
         *
         * This method sends the prepared measurement data to the ESP module for transmission over WiFi.
         */
        virtual void write() override;

        /**
         * @brief Flushes any remaining data to the ESP module.
         *
         * This method ensures that any remaining measurement data is sent to the ESP module via UART.
         */
        virtual void flush() override;

    private:
        /** @brief Reference to the UART driver used for communication with the ESP module. */
        Driver::IUartDriver &driver;
    };

}

#endif // WiFiMeasurementRecorder_H_