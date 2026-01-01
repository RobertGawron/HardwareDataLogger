#ifndef IMEASUREMENT_RECORDER_HPP
#define IMEASUREMENT_RECORDER_HPP

/**
 * @file IMeasurementRecorder.hpp
 * @brief Declaration of the IMeasurementRecorder interface class for storing measurement data.
 *
 * This file contains the declaration of the IMeasurementRecorder interface class, which serves
 * as a base class for different types of measurement recorders that store data using various mediums
 * or devices such as WiFi, UART, or SD cards.
 */

#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interface/DriverState.hpp"

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
        constexpr IMeasurementRecorder() noexcept = default;
        ~IMeasurementRecorder() override = default;

        // Non-copyable and non-movable
        IMeasurementRecorder(const IMeasurementRecorder &) = delete;
        IMeasurementRecorder(IMeasurementRecorder &&) = delete;
        IMeasurementRecorder &operator=(const IMeasurementRecorder &) = delete;
        IMeasurementRecorder &operator=(IMeasurementRecorder &&) = delete;

        /**
         * @brief Notifies about new data to be saved.
         *
         * This method should be implemented to handle any necessary actions when new data is ready to be saved.
         *
         * @param measurement The measurement data to be recorded.
         * @return true if the measurement was successfully recorded, false otherwise.
         */
        [[nodiscard]] virtual bool notify(const MeasurementType &measurement) noexcept = 0;
    };

} // namespace Device

#endif // IMEASUREMENT_RECORDER_HPP