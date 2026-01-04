#pragma once

#include "Driver/Interface/DriverComponent.hpp"
#include <concepts>
#include <cstdint>

namespace Driver::Concepts
{
    /**
     * @concept LightSensorDriver
     * @brief Concept defining requirements for ambient light sensor drivers.
     *
     * A type satisfies LightSensorDriver if it:
     * - Derives from DriverComponent
     * - Provides a getAmbientLightLevel() const method returning uint32_t
     * - Is not copyable or movable (enforced by DriverComponent)
     */
    template <typename T>
    concept LightSensorDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(const T sensor) {
            { sensor.getAmbientLightLevel() } noexcept -> std::same_as<std::uint32_t>;
        };
}
