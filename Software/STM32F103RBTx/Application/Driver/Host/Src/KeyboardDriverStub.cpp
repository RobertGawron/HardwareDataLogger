#include "KeyboardDriverStub.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"
#include "Driver/Interface/KeyState.hpp"

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

    KeyState KeyboardDriverStub::getKeyState(const KeyIdentifier key) const
    {
        const KeyState state = keyState.at(static_cast<std::uint8_t>(key));
        return state;
    }

    void KeyboardDriverStub::setKeyState(KeyIdentifier key, KeyState state)
    {
        keyState.at(static_cast<std::uint8_t>(key)) = state;
    }

}
