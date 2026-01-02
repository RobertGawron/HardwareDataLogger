/**
 * @file KeyActionState.hpp
 * @brief Defines the KeyActionState enum for key press actions.
 *
 * This file contains the definition of the KeyActionState enum, which represents
 * various actions or outcomes related to key presses on a keyboard.
 */

#ifndef KeyActionState_h_
#define KeyActionState_h_

#include <cstdint>

namespace Device
{
    /**
     * @enum KeyActionState
     * @brief Represents different actions or outcomes related to key presses.
     *
     * The KeyActionState enum is used to describe the state of a key press on a keyboard.
     * It provides different states to represent the start of a press, holding, the end of
     * a short or long press, and other relevant states.
     */
    enum class KeyActionState : std::uint8_t
    {
        PRESS_NOT = 0U,       /**< The key is in a fail mode, indicating an error or invalid state. */
        PRESS_START = 1U,     /**< The user started pressing the key. */
        PRESS_HOLD = 2U,      /**< The key is being held down. */
        PRESS_END_SHORT = 3U, /**< The press has ended and is considered a short-duration press. */
        PRESS_END_LONG = 4U,  /**< The press has ended and is considered a long-duration press. */
        FAIL = 5U             /**< The key is not currently pressed. */

    };

} // namespace Device

#endif // KeyActionState_h_