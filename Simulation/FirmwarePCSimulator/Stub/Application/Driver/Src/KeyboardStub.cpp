#include "KeyboardStub.hpp"

namespace Driver
{

    void KeyboardStub::tick()
    {
    }

    KeyboardKeyState KeyboardStub::getState(const KeyboardKeyIdentifier key) const
    {
        KeyboardKeyState state = KeyboardKeyState::NotPressed;

        return state;
    }

}
