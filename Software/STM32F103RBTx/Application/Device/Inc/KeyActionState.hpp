#ifndef KeyActionState_h_
#define KeyActionState_h_

#include <cstdint>

/**
 * @file KeyActionState.h
 * @brief Defines the KeyActionState enum for key press actions.
 *
 * This file contains the definition of the KeyActionState enum, which represents
 * various actions or outcomes related to key presses on a keyboard.
 */

namespace Device
{
    /**
     * @enum KeyActionState
     * @brief Represents different actions or outcomes related to key presses.
     *
     * The KeyActionState enum is used to describe the state of a key press on a keyboard.
     * It provides different states to represent the start of a press, the end of a short or long press,
     * and other relevant states.
     */
    enum class KeyActionState : std::uint8_t
    {
        PressStart = 0U,    /**< The user started pressing the key. */
        PressEndShort = 1U, /**< The press has ended and is considered a short-duration press. */
        PressEndLong = 2U,  /**< The press has ended and is considered a long-duration press. */
        PressNot = 3U,      /**< The key is not currently pressed. */
        Fail = 4U           /**< The key is in a fail mode, indicating an error or invalid state. */
    };

}

#endif
