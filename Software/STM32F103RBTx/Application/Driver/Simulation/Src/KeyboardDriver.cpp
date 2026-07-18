module;

#include <cstdint>

module Driver.KeyboardDriver;

namespace Driver
{
    auto KeyboardDriver::tick() noexcept -> bool
    {
        return true;
    }

    auto KeyboardDriver::getKeyState(const KeyId key) const noexcept -> KeyState
    {
        const KeyState state = keyState.at(static_cast<std::uint8_t>(key));
        return state;
    }

    auto KeyboardDriver::setKeyState(KeyId key, KeyState state) noexcept -> void
    {
        keyState.at(static_cast<std::uint8_t>(key)) = state;
    }
}