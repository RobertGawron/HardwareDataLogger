module;

#include <concepts>
#include <cstdint>

export module Driver.BrightnessDriverConcept;

import Driver.DriverComponent;

export namespace Driver::Concepts
{
    /**
     * @concept BrightnessDriverConcept
     * @brief Defines requirements for display brightness control drivers
     */
    template <typename T>
    concept BrightnessDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(T driver, std::uint8_t brightness) {
            { driver.setBrightness(brightness) } noexcept -> std::same_as<bool>;
        };
}