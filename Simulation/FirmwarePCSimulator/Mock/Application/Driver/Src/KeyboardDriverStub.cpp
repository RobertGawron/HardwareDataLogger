#include "KeyboardDriverStub.hpp"

namespace Driver
{

    bool KeyboardDriverStub::tick()
    {
        return true;
    }

    bool KeyboardDriverStub::onInitialize()
    {
        return true;
    }

    bool KeyboardDriverStub::onStart()
    {
        return true;
    }

    bool KeyboardDriverStub::onStop()
    {
        return true;
    }

    bool KeyboardDriverStub::onReset()
    {
        return true;
    }

    KeyboardKeyState KeyboardDriverStub::getKeyState(const KeyboardKeyIdentifier key) const
    {
        KeyboardKeyState state = KeyboardKeyState::NotPressed;

        return state;
    }

}