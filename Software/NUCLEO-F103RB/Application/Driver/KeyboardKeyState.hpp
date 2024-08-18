#ifndef KEYBOARDKEYSTATE_H_
#define KEYBOARDKEYSTATE_H_

namespace Driver
{
    /// @brief low level just to know if key is pressed or not.
    enum class KeyboardKeyState
    {
        Pressed = 1u,
        NotPressed = 2u
    };

}

#endif
