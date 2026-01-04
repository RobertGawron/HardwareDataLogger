#ifndef MEASUREMENT_RECORDER_BASE_HPP
#define MEASUREMENT_RECORDER_BASE_HPP

/**
 * @file MeasurementRecorderBase.hpp
 * @brief Declaration of the MeasurementRecorder concept and CRTP base for storing measurement data.
 *
 * This file contains the concept and CRTP base class for measurement recorders that store data
 * using various mediums or devices such as WiFi, UART, or SD cards.
 */

#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/DeviceComponent.hpp"

#include <concepts>

namespace Device
{
    /**
     * @brief Concept defining the measurement recorder interface
     *
     * A type satisfies MeasurementRecorder if it implements the DeviceLifecycle
     * and can be notified of new measurements.
     */
    template <typename T>
    concept MeasurementRecorder = DeviceLifecycle<T> && requires(T t, const MeasurementType &measurement) {
        { t.notify(measurement) } noexcept -> std::same_as<bool>;
    };

} // namespace Device

#endif // MEASUREMENT_RECORDER_BASE_HPP