#include "KeyboardDriverStub.hpp"
#include "Driver/Interface/KeyboardKeyIdentifier.hpp"
#include "Driver/Interface/KeyboardKeyState.hpp"

#include <cstdint>

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
        const KeyboardKeyState state = keyState.at(static_cast<std::uint8_t>(key));
        return state;
    }

    void KeyboardDriverStub::setKeyState(KeyboardKeyIdentifier key, KeyboardKeyState state)
    {
        keyState.at(static_cast<std::uint8_t>(key)) = state;
    }

}
