/**
 * @file PulseCounterMeasurementSource.hpp
 * @brief Defines the PulseCounterMeasurementSource class responsible for managing measurements
 *        from a pulse counter device.
 */

#ifndef PulseCounterMeasurementSource_H_
#define PulseCounterMeasurementSource_H_

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

namespace Device
{
    /**
     * @class PulseCounterMeasurementSource
     * @brief Manages the retrieval and initialization of measurement data from a pulse counter device.
     *
     * The PulseCounterMeasurementSource class interfaces with a pulse counter driver to initialize
     * the device, retrieve measurements, and manage the availability of new data.
     * This class provides methods to initialize, deinitialize, and query the pulse counter device for new data.
     */
    class PulseCounterMeasurementSource : public IMeasurementSource
    {
    public:
        /**
         * @brief Constructs a PulseCounterMeasurementSource with device ID and pulse counter driver.
         *
         * @param deviceId The unique identifier for this measurement source.
         * @param pulseCounterDriver Reference to the driver responsible for interfacing with the pulse counter device.
         */
        explicit PulseCounterMeasurementSource(MeasurementDeviceId deviceId, Driver::IPulseCounterDriver &pulseCounterDriver);

        PulseCounterMeasurementSource() = delete; ///< Deleted default constructor to prevent instantiation without parameters.

        /**
         * @brief Default destructor for PulseCounterMeasurementSource.
         */
        ~PulseCounterMeasurementSource() override = default;

        PulseCounterMeasurementSource(const PulseCounterMeasurementSource &) = delete;            ///< Deleted copy constructor to prevent copying.
        PulseCounterMeasurementSource &operator=(const PulseCounterMeasurementSource &) = delete; ///< Deleted assignment operator to prevent assignment.

        /**
         * @brief Initializes the pulse counter hardware and driver.
         * @return True if initialization succeeded, false otherwise.
         */
        bool initialize() override;

        /**
         * @brief Starts the pulse counter measurement process.
         * @return True if start succeeded, false otherwise.
         */
        bool start() override;

        /**
         * @brief Stops the pulse counter measurement process.
         * @return True if stop succeeded, false otherwise.
         */
        bool stop() override;

        /**
         * @brief Checks if a new measurement is available from the pulse counter.
         *
         * @return True if new measurement data is available, false otherwise.
         */
        bool isMeasurementAvailable() override;

        /**
         * @brief Retrieves the current pulse count from the pulse counter device.
         *
         * @return The current measurement data including device ID and pulse count.
         */
        MeasurementType getMeasurement() override;

    private:
        /**
         * @brief Unique identifier for this measurement source
         */
        const MeasurementDeviceId deviceId;

        /** @brief Reference to the driver responsible for interacting with the pulse counter device. */
        Driver::IPulseCounterDriver &pulseCounterDriver;
    };

}

#endif // PulseCounterMeasurementSource_H_
