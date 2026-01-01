#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/KeyActionState.hpp"
#include "Driver/Interface/KeyState.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace Device
{
    bool Keyboard::init() noexcept
    {
        if (!keyboardDriver.initialize()) [[unlikely]]
        {
            return false;
        }

        return keyboardDriver.start();
    }

    bool Keyboard::tick() noexcept
    {
        keyboardDriver.tick();

        for (std::size_t i{0}; i < keyActionState.size(); ++i)
        {
            const auto keyId = static_cast<Driver::KeyIdentifier>(i);
            const auto newState = keyboardDriver.getKeyState(keyId);
            const auto currentState = keyActionState[i];

            auto nextState = currentState;

            switch (currentState)
            {
            case KeyActionState::PressNot:
                if (newState == Driver::KeyState::Pressed)
                {
                    pressDurationTicks[i] = 0;
                    nextState = KeyActionState::PressStart;
                }
                break;

            case KeyActionState::PressStart:
                if (newState == Driver::KeyState::Pressed)
                {
                    pressDurationTicks[i]++;
                }
                else if (newState == Driver::KeyState::NotPressed)
                {
                    nextState = (pressDurationTicks[i] >= LONG_PRESS_THRESHOLD_TICKS)
                                    ? KeyActionState::PressEndLong
                                    : KeyActionState::PressEndShort;
                }
                break;

            case KeyActionState::PressEndShort:
            case KeyActionState::PressEndLong:
                if (newState == Driver::KeyState::NotPressed)
                {
                    nextState = KeyActionState::PressNot;
                }
                else if (newState == Driver::KeyState::Pressed)
                {
                    pressDurationTicks[i] = 0;
                    nextState = KeyActionState::PressStart;
                }
                break;

            case KeyActionState::Fail:
                break;
            }

            keyActionState[i] = nextState;
        }

        return true;
    }

    KeyActionState Keyboard::getKeyState(Driver::KeyIdentifier key) const noexcept
    {
        const auto index = static_cast<std::size_t>(key);

        if (index >= keyActionState.size()) [[unlikely]]
        {
            return KeyActionState::Fail;
        }

        return keyActionState[index];
    }

} // namespace Device