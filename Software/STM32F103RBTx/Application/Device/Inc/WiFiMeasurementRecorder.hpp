/**
 * @file WiFiMeasurementRecorder.hpp
 * @brief Defines the WiFiMeasurementRecorder class responsible for sending measurement data
 *        to an ESP module via UART, which then sends the data over WiFi.
 */

#ifndef WiFiMeasurementRecorder_H_
#define WiFiMeasurementRecorder_H_

#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <array>

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

        WiFiMeasurementRecorder() = delete; ///< Deleted default constructor to prevent instantiation without a driver.

        /**
         * @brief Default destructor for WiFiMeasurementRecorder.
         */
        ~WiFiMeasurementRecorder() override = default;

        WiFiMeasurementRecorder(const WiFiMeasurementRecorder &) = delete;            ///< Deleted copy constructor to prevent copying.
        WiFiMeasurementRecorder &operator=(const WiFiMeasurementRecorder &) = delete; ///< Deleted assignment operator to prevent assignment.

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available and
         * should be sent to the ESP module via UART.
         * @param measurement The measurement data to process.
         * @return True if notification was successful, false otherwise.
         */
        bool notify(Device::MeasurementType &measurement) override;

    protected:
        /**
         * @brief Initializes the WiFiMeasurementRecorder.
         *
         * This method is responsible for initializing the recorder, preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the WiFiMeasurementRecorder.
         *
         * This method starts the recorder, enabling it to begin sending measurement data via UART.
         * @return True if the recorder started successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the WiFiMeasurementRecorder.
         *
         * This method stops the recorder, halting any further transmission of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the WiFiMeasurementRecorder.
         *
         * This method resets the recorder, clearing any internal state or buffers.
         * @return True if the recorder was reset successfully, false otherwise.
         */
        bool onReset() override;

    private:
        /** @brief Reference to the UART driver used for communication with the ESP module. */
        Driver::IUartDriver &driver;

        /** @brief Size of the  message buffer. */
        static constexpr std::size_t SerializedMessageSize = 30u;

        /**
         * @brief Size of the output buffer after COBS encoding.
         *
         * Calculated according to COBS specification: ScpiBufferSize + (ScpiBufferSize / 254) + 2
         */
        static constexpr std::size_t OutputBufferSize = (SerializedMessageSize + (SerializedMessageSize / 254) + 2);

        /** @brief Buffer for storing SCPI-formatted messages. */
        std::array<std::uint8_t, SerializedMessageSize> encodedBuffer = {0};

        /** @brief Buffer for storing data after COBS encoding. */
        std::array<std::uint8_t, OutputBufferSize> dataLinkBuffer = {0};

        const uint32_t UartTxTimeout = 1000;
    };

}

#endif // WiFiMeasurementRecorder_H_
