#ifndef KeyboardKeyActionState_H_
#define KeyboardKeyActionState_H_

namespace Device
{
    /// @brief  represents different actions or outcomes related to key presses.
    enum class KeyboardKeyActionState
    {
        PressStart,
        PressEndShort,
        PressEndLong,
        PressNot,
        Fail
    };

}

#endif