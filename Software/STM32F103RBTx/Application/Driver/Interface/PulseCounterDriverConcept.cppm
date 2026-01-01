module;

#include <concepts>
#include <cstdint>

export module Driver.PulseCounterDriverConcept;

import Driver.DriverComponent;
import Driver.PulseCount;

// import Driver.PulseCounterDriverConcept;

export namespace Driver::Concepts
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
            { driver.read() } noexcept -> std::same_as<PulseCount>;
            { driver.clear() } noexcept -> std::same_as<void>;
        };
}