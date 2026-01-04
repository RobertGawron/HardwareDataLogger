module;

#include <algorithm>
#include <cstddef>
#include <cstdint>

module Device.Keyboard;

import Device.KeyActionState;

import Driver.KeyState;
import Driver.KeyIdentifier;

namespace Device
{
    auto Keyboard::onInit() noexcept -> bool
    {
        //  return keyboardDriver.init();

        return true;
    }

    auto Keyboard::onStart() noexcept -> bool
    {
        //   return keyboardDriver.start();
        return true;
    }

    auto Keyboard::onStop() noexcept -> bool
    {
        //    return keyboardDriver.stop();
        return true;
    }

    auto Keyboard::onTick() noexcept -> bool
    {
        bool status = keyboardDriver.tick();

        if (status)
        {
            for (std::size_t i{0}; i < keyActionState.size(); ++i)
            {
                const auto keyId = static_cast<Driver::KeyIdentifier>(i);
                const auto newState = keyboardDriver.getKeyState(keyId);
                const auto currentState = keyActionState[i];

                auto nextState = currentState;

                switch (currentState)
                {
                case KeyActionState::PRESS_NOT:
                    if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i] = 0;
                        nextState = KeyActionState::PRESS_START;
                    }
                    break;

                case KeyActionState::PRESS_START:
                    if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i]++;
                        nextState = KeyActionState::PRESS_HOLD;
                    }
                    else if (newState == Driver::KeyState::NotPressed)
                    {
                        nextState = (pressDurationTicks[i] >= LONG_PRESS_THRESHOLD_TICKS)
                                        ? KeyActionState::PRESS_END_LONG
                                        : KeyActionState::PRESS_END_SHORT;
                    }
                    break;

                case KeyActionState::PRESS_HOLD:
                    if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i]++;
                        // Stay in PRESS_HOLD
                    }
                    else if (newState == Driver::KeyState::NotPressed)
                    {
                        nextState = (pressDurationTicks[i] >= LONG_PRESS_THRESHOLD_TICKS)
                                        ? KeyActionState::PRESS_END_LONG
                                        : KeyActionState::PRESS_END_SHORT;
                    }
                    break;

                case KeyActionState::PRESS_END_SHORT:
                case KeyActionState::PRESS_END_LONG:
                    if (newState == Driver::KeyState::NotPressed)
                    {
                        nextState = KeyActionState::PRESS_NOT;
                    }
                    else if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i] = 0;
                        nextState = KeyActionState::PRESS_START;
                    }
                    break;

                case KeyActionState::FAIL:
                    break;
                }

                keyActionState[i] = nextState;
            }
        }

        return status;
    }

    auto Keyboard::getKeyState(Driver::KeyIdentifier key) const noexcept -> KeyActionState
    {
        const auto index = static_cast<std::size_t>(key);

        if (index >= keyActionState.size()) [[unlikely]]
        {
            return KeyActionState::FAIL;
        }

        return keyActionState[index];
    }

} // namespace Device