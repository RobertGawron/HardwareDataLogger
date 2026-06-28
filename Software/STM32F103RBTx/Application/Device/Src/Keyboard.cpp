module;

#include <algorithm>
#include <cstddef>
#include <cstdint>

module Device.Keyboard;

import Device.KeyAction;

import Driver.KeyState;
import Driver.KeyId;

namespace Device
{
    auto Keyboard::onInit() noexcept -> bool
    {
        return keyboardDriver.init();

        // return true;
    }

    auto Keyboard::onStart() noexcept -> bool
    {
        return keyboardDriver.start();
        //    return true;
    }

    auto Keyboard::onStop() noexcept -> bool
    {
        return keyboardDriver.stop();
        //  return true;
    }

    auto Keyboard::onTick() noexcept -> bool
    {
        bool status = keyboardDriver.tick();

        if (status)
        {
            for (std::size_t i{0}; i < keyAction.size(); ++i)
            {
                const auto keyId = static_cast<Driver::KeyId>(i);
                const auto newState = keyboardDriver.getKeyState(keyId);
                const auto currentState = keyAction[i];

                auto nextState = currentState;

                switch (currentState)
                {
                case KeyAction::PRESS_NOT:
                    if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i] = 0;
                        nextState = KeyAction::PRESS_START;
                    }
                    break;

                case KeyAction::PRESS_START:
                    if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i]++;
                        nextState = KeyAction::PRESS_HOLD;
                    }
                    else if (newState == Driver::KeyState::NotPressed)
                    {
                        nextState = (pressDurationTicks[i] >= LONG_PRESS_THRESHOLD_TICKS)
                                        ? KeyAction::PRESS_END_LONG
                                        : KeyAction::PRESS_END_SHORT;
                    }
                    break;

                case KeyAction::PRESS_HOLD:
                    if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i]++;
                        // Stay in PRESS_HOLD
                    }
                    else if (newState == Driver::KeyState::NotPressed)
                    {
                        nextState = (pressDurationTicks[i] >= LONG_PRESS_THRESHOLD_TICKS)
                                        ? KeyAction::PRESS_END_LONG
                                        : KeyAction::PRESS_END_SHORT;
                    }
                    break;

                case KeyAction::PRESS_END_SHORT:
                case KeyAction::PRESS_END_LONG:
                    if (newState == Driver::KeyState::NotPressed)
                    {
                        nextState = KeyAction::PRESS_NOT;
                    }
                    else if (newState == Driver::KeyState::Pressed)
                    {
                        pressDurationTicks[i] = 0;
                        nextState = KeyAction::PRESS_START;
                    }
                    break;

                case KeyAction::FAIL:
                    break;
                }

                keyAction[i] = nextState;
            }
        }

        return status;
    }

    auto Keyboard::getKeyState(Driver::KeyId key) const noexcept -> KeyAction
    {
        const auto index = static_cast<std::size_t>(key);

        if (index >= keyAction.size()) [[unlikely]]
        {
            return KeyAction::FAIL;
        }

        return keyAction[index];
    }

} // namespace Device