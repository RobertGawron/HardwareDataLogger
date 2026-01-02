#pragma once

#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/PulseCounterMeasurementSize.hpp"
#include <concepts>
#include <cstdint>

namespace Driver::Concepts
{
    /**
     * @concept PulseCounterDriverConcept
     * @brief Defines requirements for pulse counting drivers
     */
    template <typename T>
    concept PulseCounterDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(T driver) {
            // Measurement operations - use the global type alias
            { driver.getMeasurement() } noexcept -> std::same_as<PulseCounterMeasurementSize>;
            { driver.clearMeasurement() } noexcept -> std::same_as<void>;
        };
}