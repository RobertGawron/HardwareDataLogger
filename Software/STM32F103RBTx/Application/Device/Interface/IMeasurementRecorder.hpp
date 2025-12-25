#ifndef MeasurementRecorder_h
#define MeasurementRecorder_h

#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interface/DriverState.hpp"

/**
 * @file MeasurementRecorder.h
 * @brief Declaration of the IMeasurementRecorder interface class for storing measurement data.
 *
 * This file contains the declaration of the IMeasurementRecorder interface class, which serves
 * as a base class for different types of measurement recorders that store data using various mediums
 * or devices such as WiFi, UART, or SD cards.
 */

namespace Device
{
    /**
     * @class IMeasurementRecorder
     * @brief Base class for storing measurement data using various mediums or devices.
     *
     * The IMeasurementRecorder class is an interface for classes that handle the storage of measurement data.
     * It provides pure virtual methods for initializing, deinitializing, writing, flushing, and notifying about
     * new data. Derived classes implement these methods to store data using specific mediums or devices, such
     * as over WiFi, via UART, or on an SD card.
     */
    class IMeasurementRecorder : public Driver::DriverState
    {
    public:
        /**
         * @brief Default constructor.
         */
        IMeasurementRecorder() = default;

        /**
         * @brief Virtual destructor.
         */
        ~IMeasurementRecorder() override = default;

        /**
         * @brief Notifies about new data to be saved.
         *
         * This method should be implemented to handle any necessary actions when new data is ready to be saved.
         */
        virtual bool notify(Device::MeasurementType &measurement) = 0;
    };
}

#endif
