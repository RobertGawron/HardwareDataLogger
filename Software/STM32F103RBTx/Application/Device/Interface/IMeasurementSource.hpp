#ifndef IMEASUREMENT_SOURCE_HPP
#define IMEASUREMENT_SOURCE_HPP

/**
 * @file IMeasurementSource.hpp
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
        constexpr IMeasurementSource() noexcept = default;
        virtual ~IMeasurementSource() = default;

        // Non-copyable and non-movable
        IMeasurementSource(const IMeasurementSource &) = delete;
        IMeasurementSource(IMeasurementSource &&) = delete;
        IMeasurementSource &operator=(const IMeasurementSource &) = delete;
        IMeasurementSource &operator=(IMeasurementSource &&) = delete;

        /**
         * @brief Initializes the measurement source.
         * @return True if initialization succeeded, false otherwise.
         */
        [[nodiscard]] virtual bool initialize() noexcept = 0;

        /**
         * @brief Starts the measurement collection process.
         * @return True if start succeeded, false otherwise.
         */
        [[nodiscard]] virtual bool start() noexcept = 0;

        /**
         * @brief Stops the measurement collection process.
         * @return True if stop succeeded, false otherwise.
         */
        [[nodiscard]] virtual bool stop() noexcept = 0;

        /**
         * @brief Checks if a measurement is available.
         *
         * This method checks if a new measurement is ready to be retrieved. It is called
         * periodically by client classes. There might be instances where no measurement is ready,
         * depending on the data collection interval or device state.
         *
         * @return true if a measurement is available, false otherwise.
         */
        [[nodiscard]] virtual bool isMeasurementAvailable() const noexcept = 0;

        /**
         * @brief Retrieves the measured data.
         *
         * This method obtains the current measurement data from the device.
         *
         * @return The current measurement data.
         */
        [[nodiscard]] virtual MeasurementType getMeasurement() noexcept = 0;
    };

} // namespace Device

#endif // IMEASUREMENT_SOURCE_HPP