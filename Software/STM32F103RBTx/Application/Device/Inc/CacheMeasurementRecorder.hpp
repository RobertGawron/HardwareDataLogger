
#ifndef CacheMeasurementRecorder_H_
#define CacheMeasurementRecorder_H_

#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Device/Interfaces/IMeasurementReader.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include <array>
#include <cstdint>

namespace Device
{

    class CacheMeasurementRecorder : public IMeasurementRecorder, public IMeasurementReader
    {
    public:
        /**
         * @brief Deleted default constructor to prevent instantiation without a driver.
         */
        CacheMeasurementRecorder() = default;

        /**
         * @brief Default destructor for CacheMeasurementRecorder.
         */
        ~CacheMeasurementRecorder() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        CacheMeasurementRecorder(const CacheMeasurementRecorder &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return CacheMeasurementRecorder& The assigned object.
         */
        CacheMeasurementRecorder &operator=(const CacheMeasurementRecorder &) = delete;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available and
         * should be sent to the ESP module via UART.
         */
        bool notify(Device::MeasurementType &measurement) override;

    protected:
        /**
         * @brief Initializes the CacheMeasurementRecorder.
         *
         * This method is responsible for initializing the recorder, preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the CacheMeasurementRecorder.
         *
         * This method starts the recorder, enabling it to begin sending measurement data via UART.
         * @return True if the recorder started successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the CacheMeasurementRecorder.
         *
         * This method stops the recorder, halting any further transmission of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the CacheMeasurementRecorder.
         *
         * This method resets the recorder, clearing any internal state or buffers.
         * @return True if the recorder was reset successfully, false otherwise.
         */
        bool onReset() override;

        /**
         * @brief Flushes any remaining data to the ESP module.
         *
         * This method ensures that any remaining measurement data is sent to the ESP module via UART.
         */
        bool flush() override;

        [[nodiscard]] std::uint32_t getLatestMeasurement(Device::MeasurementDeviceId source) const override;

    private:
        /**
         * @brief Writes the measurement data to the ESP module via UART.
         *
         * This method sends the prepared measurement data to the ESP module for transmission over WiFi.
         */
        virtual bool write(Device::MeasurementType &measurement);

        static constexpr std::size_t MeasurementSourceCount = static_cast<std::size_t>(MeasurementDeviceId::LAST_NOT_USED);

        // Map to store the last measurements for each source
        std::array<std::uint32_t, MeasurementSourceCount> lastMeasurement = {0u};
    };

}

#endif // CacheMeasurementRecorder_H_
