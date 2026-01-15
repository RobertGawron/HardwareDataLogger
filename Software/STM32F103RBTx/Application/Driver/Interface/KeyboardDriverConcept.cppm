module;

#include <concepts>

export module Driver.KeyboardDriverConcept;

import Driver.DriverComponent;
import Driver.KeyState;
import Driver.KeyIdentifier;

export namespace Driver::Concepts
{
    /**
     * @concept KeyboardDriver
     * @brief Defines requirements for keyboard/button input drivers
     */
    template <typename T>
    concept KeyboardDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(T driver, const T constDriver, KeyIdentifier key) {
            { driver.tick() } noexcept -> std::same_as<bool>;
            { constDriver.getKeyState(key) } noexcept -> std::same_as<KeyState>;
        };
}