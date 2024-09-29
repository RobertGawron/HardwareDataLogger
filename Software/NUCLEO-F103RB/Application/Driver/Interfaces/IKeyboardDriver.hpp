/**
 * @file IKeyboardDriver.hpp
 * @brief Defines the IKeyboardDriver interface for interacting with a keyboard consisting of hardware push buttons.
 */

#ifndef DRIVER_IKEYBOARDKEYSDRIVER_H_
#define DRIVER_IKEYBOARDKEYSDRIVER_H_

#include "Driver/Inc/KeyboardKeyState.hpp"
#include "Driver/Inc/KeyboardKeyIdentifier.hpp"
#include "Driver/Inc/DriverState.hpp"
#include <stdint.h>

namespace Driver
{

    /**
     * @class IKeyboardDriver
     * @brief Interface for keyboard drivers to handle hardware push button input.
     *
     * This interface provides a set of pure virtual functions that must be implemented
     * by any keyboard driver. It includes basic operations like initializing the driver,
     * periodically updating its state, and reading the state of individual keys.
     */
    class IKeyboardDriver : public DriverState
    {
    public:
        /**
         * @brief Default constructor for IKeyboardDriver.
         */
        IKeyboardDriver() = default;

        /**
         * @brief Virtual destructor for IKeyboardDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IKeyboardDriver() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        IKeyboardDriver(const IKeyboardDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return IKeyboardDriver& The assigned object.
         */
        IKeyboardDriver &operator=(const IKeyboardDriver &) = delete;

        /**
         * @brief Periodically updates the state of the keyboard.
         *
         * This function should be called regularly (e.g., in a timer interrupt or main loop) to update
         * the state of the push buttons.
         *
         * @return True if the keyboard state was successfully updated, false otherwise.
         */
        virtual bool tick() = 0;

        /**
         * @brief Gets the current state of a specified key.
         *
         * This function returns the raw state (pressed or not pressed) of a given key identified by `key`.
         * The state is considered "low level," meaning that no long/short press detection or debouncing
         * is performed at this level; it is merely the state read from the GPIO connected to the key.
         *
         * @param key The identifier of the key whose state is requested.
         * @return The current state of the key (`KeyboardKeyState`).
         */
        virtual KeyboardKeyState getKeyState(const KeyboardKeyIdentifier key) const = 0;
    };

}

#endif // DRIVER_IKEYBOARDKEYSDRIVER_H_