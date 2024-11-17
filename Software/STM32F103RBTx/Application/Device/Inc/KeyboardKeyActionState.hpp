#ifndef KeyboardKeyActionState_h_
#define KeyboardKeyActionState_h_

/**
 * @file KeyboardKeyActionState.h
 * @brief Defines the KeyboardKeyActionState enum for key press actions.
 *
 * This file contains the definition of the KeyboardKeyActionState enum, which represents
 * various actions or outcomes related to key presses on a keyboard.
 */

namespace Device
{
    /**
     * @enum KeyboardKeyActionState
     * @brief Represents different actions or outcomes related to key presses.
     *
     * The KeyboardKeyActionState enum is used to describe the state of a key press on a keyboard.
     * It provides different states to represent the start of a press, the end of a short or long press,
     * and other relevant states.
     */
    enum class KeyboardKeyActionState : uint8_t
    {
        PressStart,    /**< The user started pressing the key. */
        PressEndShort, /**< The press has ended and is considered a short-duration press. */
        PressEndLong,  /**< The press has ended and is considered a long-duration press. */
        PressNot,      /**< The key is not currently pressed. */
        Fail           /**< The key is in a fail mode, indicating an error or invalid state. */
    };

}

#endif
