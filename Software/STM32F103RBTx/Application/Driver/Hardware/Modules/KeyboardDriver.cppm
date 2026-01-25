module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "main.h"

#include <array>
#include <cstdint>
#include <utility>

export module Driver.KeyboardDriver;

import Driver.DriverComponent;
import Driver.KeyboardDriverConcept;
import Driver.KeyState;
import Driver.KeyId;

export namespace Driver
{
    /**
     * @class KeyboardDriver
     * @brief Keyboard/button input driver.
     *
     * Provides polled access to a fixed set of keys defined at compile time.
     * The driver is intended for active-low buttons with pull-ups enabled.
     *
     * @note Debouncing is not performed by this driver.
     */
    class KeyboardDriver final : public DriverComponent
    {
    public:
        KeyboardDriver() = default;
        ~KeyboardDriver() = default;

        KeyboardDriver(const KeyboardDriver &) = delete;
        KeyboardDriver &operator=(const KeyboardDriver &) = delete;
        KeyboardDriver(KeyboardDriver &&) = delete;
        KeyboardDriver &operator=(KeyboardDriver &&) = delete;

        /**
         * @brief Updates the internal key sampling state.
         *
         * @retval true  The driver is operational and sampling state was updated.
         * @retval false The driver is not operational and sampling state was not updated.
         */
        [[nodiscard]] bool tick() noexcept;

        /**
         * @brief Returns the current state of a key.
         *
         * @param key Key identifier.
         * @return KeyState::Pressed / KeyState::NotPressed when operational and key is valid.
         * @return KeyState::UnknownKeyAsked when @p key is invalid.
         * @return KeyState::DriverNotOperational when the driver is not operational.
         */
        [[nodiscard]] KeyState getKeyState(KeyId key) const noexcept;

    private:
        /// Cached sampling state used to derive per-key states.
        std::uint32_t gpioSnapshot{0U};
    };

    /** @brief Ensures KeyboardDriver satisfies the project keyboard driver interface. */
    static_assert(Driver::Concepts::KeyboardDriverConcept<KeyboardDriver>,
                  "KeyboardDriver must satisfy KeyboardDriverConcept requirements");
}