#ifndef IMeasurementSource_h
#define IMeasurementSource_h

/**
 * @file IMeasurementSource.h
 * @brief Declaration of the IMeasurementSource interface class for receiving measurement data.
 *
 * This file contains the declaration of the IMeasurementSource interface class, which serves
 * as a base class for classes that receive measurement data from various sources, such as GPIO
 * pulse counters or UART devices.
 */

#include "Device/Inc/MeasurementType.hpp"

namespace Device
{
    /**
     * @class IMeasurementSource
     * @brief Base class for receiving measurement data from various sources.
     *
     * The IMeasurementSource class is an interface for classes that handle the reception of measurement data
     * from different sources. These classes are responsible for establishing communication with the device and
     * preparing the measurement data so it can be later stored and parsed by other components.
     */
    class IMeasurementSource
    {
    public:
        /**
         * @brief Default constructor.
         */
        IMeasurementSource() = default;

        /**
         * @brief Virtual destructor.
         */
        virtual ~IMeasurementSource() = default;

        virtual bool initialize() = 0;
        virtual bool start() = 0;
        virtual bool stop() = 0;

        /**
         * @brief Checks if a measurement is available.
         *
         * This method should be implemented to check if a new measurement is ready to be retrieved. It is called
         * periodically by client classes. There might be instances where no measurement is ready, depending on
         * the data collection interval or device state.
         *
         * @return true if a measurement is available, false otherwise.
         */
        virtual bool isMeasurementAvailable() = 0;

        /**
         * @brief Retrieves the measured data.
         *
         * This method should be implemented to obtain the current measurement data from the device.
         * It is not fully implemented yet.
         */
        virtual MeasurementType getMeasurement() = 0;
    };
}

#endif
