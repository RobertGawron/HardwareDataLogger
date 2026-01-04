/**
 * @file MeasurementSource.cppm
 * @brief Declaration of the MeasurementSource interface concept for receiving measurement data.
 *
 * This file contains the declaration of the MeasurementSource concept, which serves
 * as an interface for classes that receive measurement data from various sources, such as GPIO
 * pulse counters or UART devices.
 */
module;

#include <concepts>

export module Device.MeasurementSource;

import Device.DeviceComponent;
import Device.MeasurementType;

export namespace Device
{
    /**
     * @brief Concept defining the measurement source interface
     *
     * A type satisfies MeasurementSource if it implements the DeviceLifecycle
     * and can provide measurement availability and data.
     */
    template <typename T>
    concept MeasurementSource = DeviceLifecycle<T> && requires(T t, const T ct) {
        { ct.isMeasurementAvailable() } noexcept -> std::same_as<bool>;
        { t.getMeasurement() } noexcept -> std::same_as<MeasurementType>;
    };

} // namespace Device