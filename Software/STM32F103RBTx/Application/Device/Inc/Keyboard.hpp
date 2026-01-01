#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

/**
 * @file Keyboard.hpp
 * @brief Declaration of the Keyboard class for handling keyboard inputs.
 *
 * This file contains the declaration of the Keyboard class, which is responsible for
 * debouncing key presses and detecting long and short key press actions.
 */

#include "Device/Interface/IKeyboard.hpp"
#include "Device/Inc/KeyActionState.hpp"
#include "Driver/Interface/IKeyboardDriver.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"

#include <array>
#include <cstdint>

namespace Device
{
    /**
     * @class Keyboard
     * @brief Handles debouncing and detecting long/short key presses.
     *
     * The Keyboard class provides functionality for initializing a keyboard, debouncing key presses,
     * and detecting whether keys are pressed in a long or short duration. It interacts with a platform-specific
     * keyboard driver to handle low-level key press events.
     */
    class Keyboard final : public IKeyboard
    {
    public:
        /**
         * @brief Constructs a Keyboard object with the given keyboard driver.
         *
         * Initializes the Keyboard instance with a reference to a platform-specific keyboard driver.
         *
         * @param keyboardDriver A reference to a platform-specific keyboard driver implementing IKeyboardDriver.
         */
        explicit constexpr Keyboard(Driver::IKeyboardDriver &keyboardDriver) noexcept
            : keyboardDriver{keyboardDriver}
        {
        }

        ~Keyboard() override = default;

        // Non-copyable and non-movable
        Keyboard(const Keyboard &) = delete;
        Keyboard(Keyboard &&) = delete;
        Keyboard &operator=(const Keyboard &) = delete;
        Keyboard &operator=(Keyboard &&) = delete;

        /**
         * @brief Initializes the keyboard.
         *
         * Sets up necessary configurations for handling key inputs, including debouncing and state management.
         *
         * @return true if initialization is successful, false otherwise.
         */
        [[nodiscard]] bool init() noexcept override;

        /**
         * @brief Ticks the keyboard state machine.
         *
         * Updates the keyboard state machine to handle debouncing of key presses and update key states.
         * This method should be called periodically.
         *
         * @return true if the tick operation was successful, false otherwise.
         */
        [[nodiscard]] bool tick() noexcept override;

        /**
         * @brief Gets the action state of a specified key.
         *
         * Retrieves the current action state of the specified key, such as whether it is pressed, held down, or released.
         *
         * @param key The ID of the key for which the state is requested.
         * @return The action state of the specified key.
         */
        [[nodiscard]] KeyActionState getKeyState(Driver::KeyIdentifier key) const noexcept override;

    private:
        Driver::IKeyboardDriver &keyboardDriver;

        static constexpr std::uint8_t AMOUNT_OF_KEYS{
            static_cast<std::uint8_t>(Driver::KeyIdentifier::LastNotUsed)};

        static constexpr std::uint8_t LONG_PRESS_THRESHOLD_TICKS{10}; // 10 ticks * 100ms = 1 second

        /**
         * @brief Array for tracking the duration (in ticks) each key has been pressed.
         *
         * Each entry counts the number of `tick()` calls while the key is pressed.
         */
        std::array<std::uint8_t, AMOUNT_OF_KEYS> pressDurationTicks{};

        /**
         * @brief Array storing the action states for all keys.
         *
         * Each key's action state indicates whether it is pressed, held, or not pressed.
         */
        std::array<KeyActionState, AMOUNT_OF_KEYS> keyActionState{};
    };

} // namespace Device

#endif // KEYBOARD_HPP