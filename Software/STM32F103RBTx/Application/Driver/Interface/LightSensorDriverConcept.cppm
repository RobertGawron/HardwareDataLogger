module;

#include <concepts>
#include <cstdint>
#include <span>

export module Driver.LightSensorDriverConcept;

import Driver.DriverComponent;

export namespace Driver::Concepts
{
    /**
     * @concept LightSensorDriver
     * @brief Concept defining requirements for ambient light sensor drivers.
     *
     * A type satisfies LightSensorDriver if it:
     * - Derives from DriverComponent
     * - Provides a samples() const method returning std::span<const std::uint16_t>
     * - Is not copyable or movable (enforced by DriverComponent)
     */
    template <typename T>
    concept LightSensorDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(const T sensor) {
            { sensor.samples() } noexcept -> std::same_as<std::span<const std::uint16_t>>;
        };
}