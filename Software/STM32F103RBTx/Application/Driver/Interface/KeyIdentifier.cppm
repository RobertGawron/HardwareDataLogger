module;

#include <cstdint>

export module Driver.KeyIdentifier;

/**
 * @file KeyIdentifier.hpp
 * @brief Defines the KeyIdentifier enum for identifying keyboard keys.
 *
 * This file contains the definition of the KeyIdentifier enum, which assigns unique values
 * to different keys on a keyboard. It allows for easy expansion if more keys are added.
 */

export namespace Driver
{
    /**
     * @enum KeyIdentifier
     * @brief Assigns unique identifiers to keyboard keys.
     *
     * The KeyIdentifier enum is used to represent different keys on a keyboard with unique
     * integer values. This allows for easy identification and handling of different key inputs.
     * Currently, there are four keys defined, but more can be added as needed.
     */
    enum class KeyIdentifier : std::uint8_t
    {
        Up = 0U,         /**< Represents the 'Up' key, assigned with value 0. */
        Down = 1U,       /**< Represents the 'Down' key, assigned with value 1. */
        Left = 2U,       /**< Represents the 'Left' key, assigned with value 2. */
        Right = 3U,      /**< Represents the 'Right' key, assigned with value 3. */
        LastNotUsed = 4U /**< Represents the last enum value, used to determine the size of the enum. */
    };

}