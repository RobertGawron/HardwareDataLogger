#ifndef KeyboardKeyIdentifier_h
#define KeyboardKeyIdentifier_h

#include <cstdint>

/**
 * @file KeyboardKeyIdentifier.hpp
 * @brief Defines the KeyboardKeyIdentifier enum for identifying keyboard keys.
 *
 * This file contains the definition of the KeyboardKeyIdentifier enum, which assigns unique values
 * to different keys on a keyboard. It allows for easy expansion if more keys are added.
 */

namespace Driver
{
    /**
     * @enum KeyboardKeyIdentifier
     * @brief Assigns unique identifiers to keyboard keys.
     *
     * The KeyboardKeyIdentifier enum is used to represent different keys on a keyboard with unique
     * integer values. This allows for easy identification and handling of different key inputs.
     * Currently, there are four keys defined, but more can be added as needed.
     */
    enum class KeyboardKeyIdentifier : std::uint8_t
    {
        Up = 0u,         /**< Represents the 'Up' key, assigned with value 0. */
        Down = 1u,       /**< Represents the 'Down' key, assigned with value 1. */
        Left = 2u,       /**< Represents the 'Left' key, assigned with value 2. */
        Right = 3u,      /**< Represents the 'Right' key, assigned with value 3. */
        LastNotUsed = 4u /**< Represents the last enum value, used to determine the size of the enum. */
    };

}

#endif
