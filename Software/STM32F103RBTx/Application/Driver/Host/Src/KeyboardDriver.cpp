#include "KeyboardDriver.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"
#include "Driver/Interface/KeyState.hpp"

#include <cstdint>

namespace Driver
{

    bool KeyboardDriver::tick() noexcept
    {
        return true;
    }

    KeyState KeyboardDriver::getKeyState(const KeyIdentifier key) const noexcept
    {
        const KeyState state = keyState.at(static_cast<std::uint8_t>(key));
        return state;
    }

    void KeyboardDriver::setKeyState(KeyIdentifier key, KeyState state) noexcept
    {
        keyState.at(static_cast<std::uint8_t>(key)) = state;
    }

}
