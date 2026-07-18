module;

#include <array>
#include <cstdint>

export module Driver.KeyboardDriver;

import Driver.DriverComponent;
import Driver.KeyboardDriverConcept;
import Driver.KeyState;
import Driver.KeyId;

export namespace Driver
{
    class KeyboardDriver : public DriverComponent
    {
    public:
        KeyboardDriver() = default;

        ~KeyboardDriver() = default;

        // Non-copyable and non-movable
        KeyboardDriver(const KeyboardDriver &) = delete;
        KeyboardDriver(KeyboardDriver &&) = delete;
        KeyboardDriver &operator=(const KeyboardDriver &) = delete;
        KeyboardDriver &operator=(KeyboardDriver &&) = delete;

        /**
         * @brief Periodically checks the state of the push buttons.
         *
         * This function should be called regularly (e.g., in a timer interrupt or main loop) to update
         * the state of the buttons.
         */
        auto tick() noexcept -> bool;

        /**
         * @brief Gets the current state of a specified button.
         *
         * This function returns the state (pressed or not pressed) of a given button identified by `key`.
         *
         * @param key The identifier of the button whose state is requested.
         * @return The current state of the button (`KeyState`).
         */
        [[nodiscard]] auto getKeyState(KeyId key) const noexcept -> KeyState;

        /**
         * @brief Sets the state of a specific key.
         *
         * @param key The identifier of the button whose state should be set.
         * @param state The new state to set for the button.
         */
        auto setKeyState(KeyId key, KeyState state) noexcept -> void;

    private:
        /**
         * @brief Number of keys supported by the keyboard.
         *
         * This constant defines the total number of keys that are supported by the keyboard driver.
         * It is derived from the last unused key identifier.
         */
        static constexpr std::uint8_t AmountOfKeys = static_cast<std::uint8_t>(Driver::KeyId::LAST_NOT_USED);

        std::array<KeyState, AmountOfKeys> keyState{KeyState::NotPressed};
    };
}