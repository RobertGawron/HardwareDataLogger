#ifndef Keyboard_h
#define Keyboard_h

/**
 * @file Keyboard.hpp
 * @brief Declaration of the Keyboard class for handling keyboard inputs.
 *
 * This file contains the declaration of the Keyboard class, which is responsible for
 * debouncing key presses and detecting long and short key press actions.
 */

#include "Device/Interfaces/IKeyboard.hpp"
#include "Driver/Interfaces/IKeyboardDriver.hpp"
#include "Device/Inc/KeyboardKeyActionState.hpp"
#include "Driver/Inc/KeyboardKeyIdentifier.hpp"

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
    class Keyboard : public IKeyboard
    {
    public:
        /**
         * @brief Constructs a Keyboard object with the given keyboard driver.
         *
         * Initializes the Keyboard instance with a reference to a platform-specific keyboard driver.
         *
         * @param keyboardDriver A reference to a platform-specific keyboard driver implementing IKeyboardDriver.
         */
        explicit Keyboard(Driver::IKeyboardDriver &keyboardDriver);

        /**
         * @brief Default destructor.
         *
         * Cleans up resources used by the Keyboard instance.
         */
        virtual ~Keyboard() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         *
         * Prevents the copying of Keyboard instances.
         */
        Keyboard(const Keyboard &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent copying.
         *
         * Prevents assignment of Keyboard instances.
         * @return Keyboard& Reference to this object.
         */
        Keyboard &operator=(const Keyboard &) = delete;

        /**
         * @brief Initializes the keyboard.
         *
         * Sets up necessary configurations for handling key inputs, including debouncing and state management.
         *
         * @return true if initialization is successful, false otherwise.
         */
        virtual bool init() override;

        /**
         * @brief Ticks the keyboard state machine.
         *
         * Updates the keyboard state machine to handle debouncing of key presses and update key states.
         * This method should be called periodically.
         */
        virtual bool tick() override;

        /**
         * @brief Gets the action state of a specified key.
         *
         * Retrieves the current action state of the specified key, such as whether it is pressed, held down, or released.
         *
         * @param key The ID of the key for which the state is requested.
         * @return The action state of the specified key.
         */
        virtual KeyboardKeyActionState getKeyState(Driver::KeyboardKeyIdentifier key) const override;

    private:
        Driver::IKeyboardDriver &keyboardDriver; /**< Reference to the platform-specific keyboard driver. */

        static constexpr uint8_t AmountOfKeys = static_cast<uint8_t>(Driver::KeyboardKeyIdentifier::LastNotUsed); /**< Number of keys supported by the keyboard. */
        KeyboardKeyActionState keyActionState[AmountOfKeys]{
            KeyboardKeyActionState::PressNot,
            KeyboardKeyActionState::PressNot,
            KeyboardKeyActionState::PressNot,
            KeyboardKeyActionState::PressNot}; /**< Array storing the action states for all keys. */
    };

}

#endif