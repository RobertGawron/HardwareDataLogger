/**
 * @file MeasurementRecorder.cppm
 * @brief Declaration of the MeasurementRecorder concept for storing measurement data.
 *
 * This file contains the concept for measurement recorders that store data
 * using various mediums or devices such as WiFi, UART, or SD cards.
 */
module;

#include <concepts>

export module Device.MeasurementRecorder;

import Device.MeasurementType;
import Device.DeviceComponent;

export namespace Device
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