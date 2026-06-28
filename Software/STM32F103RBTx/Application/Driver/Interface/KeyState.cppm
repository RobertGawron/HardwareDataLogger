module;

#include <cstdint>

export module Driver.KeyState;

/**
 * @file KeyState.hpp
 * @brief Defines the KeyState enum for indicating the low-level state of a keyboard key.
 */

export namespace Driver
{
    /**
     * @enum KeyState
     * @brief Represents the low-level state of a keyboard key.
     *
     * The KeyState enum is used to indicate whether a keyboard key is pressed or not
     * at a low level. This enum does not handle more complex states, such as distinguishing
     * between long or short presses, nor does it handle debouncing. Higher-level classes in
     * the Device namespace are responsible for implementing these additional behaviors.
     */
    enum class KeyState : std::uint8_t
    {
        Pressed = 1U,             /**< The key is currently pressed. */
        NotPressed = 2U,          /**< The key is currently not pressed. */
        DriverNotOperational = 3, /**< The key cannot be checked, driver is not in not running. */
        UnknownKeyAsked = 4       /**< The key doesn't exists. */
    };

}