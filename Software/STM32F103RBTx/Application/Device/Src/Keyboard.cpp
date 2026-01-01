#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/KeyActionState.hpp"
#include "Driver/Interface/KeyState.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"
#include "Driver/Interface/IKeyboardDriver.hpp"

#include <cstdint>
#include <cstddef> // For std::size_t

namespace Device
{
    Keyboard::Keyboard(::Driver::IKeyboardDriver &_keyboardDriver) : keyboardDriver(_keyboardDriver)
    {
    }

    bool Keyboard::init()
    {
        bool status = keyboardDriver.initialize();

        if (status)
        {
            status = keyboardDriver.start();
        }
        return status;
    }

    bool Keyboard::tick()
    {
        keyboardDriver.tick();

        for (std::size_t i = 0; i < keyActionState.size(); ++i)
        {
            const auto keyId = static_cast<::Driver::KeyIdentifier>(i);
            const auto newState = keyboardDriver.getKeyState(keyId);

            const auto currentState = keyActionState[i];
            auto nextState = currentState; // Default to no change

            switch (currentState)
            {
            case KeyActionState::PressNot:
                if (newState == Driver::KeyState::Pressed)
                {
                    // Key just got pressed
                    pressDurationTicks[i] = 0; // Reset duration counter
                    nextState = KeyActionState::PressStart;
                }
                break;

            case KeyActionState::PressStart:
                if (newState == Driver::KeyState::Pressed)
                {
                    // Key is held down, increment the duration counter
                    pressDurationTicks[i]++;
                }
                else if (newState == Driver::KeyState::NotPressed)
                {
                    // Key released, check how long it was pressed
                    if (pressDurationTicks[i] >= LONG_PRESS_THRESHOLD_TICKS)
                    {
                        nextState = KeyActionState::PressEndLong;
                    }
                    else
                    {
                        nextState = KeyActionState::PressEndShort;
                    }
                }
                break;

            case KeyActionState::PressEndShort:
            case KeyActionState::PressEndLong:
                // After a short/long press concluded
                if (newState == Driver::KeyState::NotPressed)
                {
                    // Go back to PressNot if still not pressed
                    nextState = KeyActionState::PressNot;
                }
                else if (newState == Driver::KeyState::Pressed)
                {
                    // Key got pressed again
                    pressDurationTicks[i] = 0;
                    nextState = KeyActionState::PressStart;
                }
                break;

            case KeyActionState::Fail:
                // TODO
                // default:
                // If there are other states or error conditions, handle them here
                break;
            default:
            {
            }
            break;
            }

            keyActionState[i] = nextState;
        }

        return true;
    }

    KeyActionState Keyboard::getKeyState(::Driver::KeyIdentifier key) const
    {
        // Use std::find_if for safe lookup
        auto index = static_cast<std::uint8_t>(key);
        if (index >= keyActionState.size())
        {
            return KeyActionState::Fail;
        }

        return keyActionState[index];
    }

}
