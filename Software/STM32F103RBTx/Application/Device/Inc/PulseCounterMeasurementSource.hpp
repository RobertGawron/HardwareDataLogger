/**
 * @file PulseCounterMeasurementSource.hpp
 * @brief Defines the PulseCounterMeasurementSource class responsible for managing measurements
 *        from a pulse counter device.
 */

#ifndef PulseCounterMeasurementSource_H_
#define PulseCounterMeasurementSource_H_

#include "Device/Interfaces/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Inc/PulseCounterDriver.hpp"

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
        using MeasurementSizeType = Driver::IPulseCounterDriver::CounterSizeType;

        /**
         * @brief Constructs a PulseCounterMeasurementSource with a reference to a PulseCounterDriver.
         *
         * @param pulseCounterDriver Reference to the driver responsible for interfacing with the pulse counter device.
         */
        explicit PulseCounterMeasurementSource(MeasurementDeviceId id, Driver::IPulseCounterDriver &pulseCounterDriver);

        /**
         * @brief Deleted default constructor to prevent instantiation without a driver.
         */
        PulseCounterMeasurementSource() = delete;

        /**
         * @brief Default destructor for PulseCounterMeasurementSource.
         */
        ~PulseCounterMeasurementSource() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        PulseCounterMeasurementSource(const PulseCounterMeasurementSource &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return PulseCounterMeasurementSource& The assigned object.
         */
        PulseCounterMeasurementSource &operator=(const PulseCounterMeasurementSource &) = delete;

        bool initialize() override;
        bool start() override;
        bool stop() override;

        /**
         * @brief Checks if a new measurement is available from the pulse counter.
         *
         * @return True if new measurement data is available, false otherwise.
         */
        bool isMeasurementAvailable() override;

        /**
         * @brief Retrieves the current pulse count from the pulse counter device.
         */
        MeasurementType getMeasurement() override;

    private:
        /** @brief Reference to the driver responsible for interacting with the pulse counter device. */
        Driver::IPulseCounterDriver &pulseCounterDriver;
    };

}

#endif // PulseCounterMeasurementSource_H_
