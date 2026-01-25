module;

#include <cstdint>
#include <type_traits>

export module Driver.KeyId;

/**
 * @file KeyId.hpp
 * @brief Defines the KeyId enum for identifying keyboard keys.
 *
 * This file contains the definition of the KeyId enum, which assigns unique values
 * to different keys on a keyboard. It allows for easy expansion if more keys are added.
 */

export namespace Driver
{
    /**
     * @enum KeyId
     * @brief Assigns unique identifiers to keyboard keys.
     *
     * The KeyId enum is used to represent different keys on a keyboard with unique
     * integer values. This allows for easy identification and handling of different key inputs.
     * Currently, there are four keys defined, but more can be added as needed.
     */
    enum class KeyId : std::uint8_t
    {
        Up = 0U,         /**< Represents the 'Up' key, assigned with value 0. */
        Down = 1U,       /**< Represents the 'Down' key, assigned with value 1. */
        Left = 2U,       /**< Represents the 'Left' key, assigned with value 2. */
        Right = 3U,      /**< Represents the 'Right' key, assigned with value 3. */
        LastNotUsed = 4U /**< Represents the last enum value, used to determine the size of the enum. */
    };

    static_assert(std::is_enum_v<KeyId>, "KeyId must remain an enum type");

    static_assert(std::is_same_v<std::underlying_type_t<KeyId>, std::uint8_t>,
                  "KeyId underlying type must be std::uint8_t");

    static_assert(static_cast<std::uint8_t>(KeyId::Up) == 0U,
                  "KeyId::Up must be 0");

    static_assert(static_cast<std::uint8_t>(KeyId::Down) == 1U,
                  "KeyId::Down must be 1");

    static_assert(static_cast<std::uint8_t>(KeyId::Left) == 2U,
                  "KeyId::Left must be 2");

    static_assert(static_cast<std::uint8_t>(KeyId::Right) == 3U,
                  "KeyId::Right must be 3");

    static_assert(static_cast<std::uint8_t>(KeyId::LastNotUsed) == 4U,
                  "KeyId::LastNotUsed must be 4 (number of keys)");

    constexpr bool isValid(KeyId k) noexcept
    {
        using U = std::underlying_type_t<KeyId>;
        return static_cast<U>(k) < static_cast<U>(KeyId::LastNotUsed);
    }

}