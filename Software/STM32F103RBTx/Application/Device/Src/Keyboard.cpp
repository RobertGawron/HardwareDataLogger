#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/KeyActionState.hpp"
#include "Driver/Interface/KeyState.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace Device
{
    bool Keyboard::onInit() noexcept
    {
        //  return keyboardDriver.init();

        return true;
    }

    bool Keyboard::onStart() noexcept
    {
        //   return keyboardDriver.start();
        return true;
    }

    bool Keyboard::onStop() noexcept
    {
        //    return keyboardDriver.stop();
        return true;
    }

    bool Keyboard::onTick() noexcept
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

    KeyActionState Keyboard::getKeyState(Driver::KeyIdentifier key) const noexcept
    {
        const auto index = static_cast<std::size_t>(key);

        if (index >= keyActionState.size()) [[unlikely]]
        {
            return KeyActionState::FAIL;
        }

        return keyActionState[index];
    }

} // namespace Device