/**
 * @file PulseCounterMeasurementSource.hpp
 * @brief Defines the PulseCounterMeasurementSource class responsible for managing measurements
 *        from a pulse counter device.
 */

#ifndef PulseCounterMeasurementSource_H_
#define PulseCounterMeasurementSource_H_

#include "IMeasurementSource.hpp"
#include "PulseCounterDriver.hpp"

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
         * @brief Constructs a PulseCounterMeasurementSource with a reference to a PulseCounterDriver.
         *
         * @param pulseCounterDriver Reference to the driver responsible for interfacing with the pulse counter device.
         */
        explicit PulseCounterMeasurementSource(Driver::IPulseCounterDriver &pulseCounterDriver);

        /**
         * @brief Deleted default constructor to prevent instantiation without a driver.
         */
        PulseCounterMeasurementSource() = delete;

        /**
         * @brief Default destructor for PulseCounterMeasurementSource.
         */
        virtual ~PulseCounterMeasurementSource() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        PulseCounterMeasurementSource(const PulseCounterMeasurementSource &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return PulseCounterMeasurementSource& The assigned object.
         */
        PulseCounterMeasurementSource &operator=(const PulseCounterMeasurementSource &) = delete;

        /**
         * @brief Initializes the pulse counter, setting the initial pulse count to zero.
         *
         * @return True if initialization was successful, false otherwise.
         */
        virtual bool init() override;

        /**
         * @brief Deinitializes the pulse counter device.
         *
         * @return True if deinitialization was successful, false otherwise.
         */
        virtual bool deinit() override;

        /**
         * @brief Checks if a new measurement is available from the pulse counter.
         *
         * @return True if new measurement data is available, false otherwise.
         */
        virtual bool isMeasurementAvailable() override;

        /**
         * @brief Retrieves the current pulse count from the pulse counter device.
         */
        virtual void getMeasurement() override;

    private:
        /** @brief Reference to the driver responsible for interacting with the pulse counter device. */
        Driver::IPulseCounterDriver &pulseCounterDriver;
    };

}

#endif // PulseCounterMeasurementSource_H_