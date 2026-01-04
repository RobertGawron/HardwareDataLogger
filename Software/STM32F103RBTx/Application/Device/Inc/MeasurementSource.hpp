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
#include "Device/Inc/DeviceComponent.hpp"

#include <concepts>

namespace Device
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

#endif // IMEASUREMENT_SOURCE_HPP