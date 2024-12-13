#include "Device/Inc/Keyboard.hpp"
#include "Driver/Inc/KeyboardKeyState.hpp"
#include "Device/Inc/KeyboardKeyActionState.hpp"

// for test of driver lib
#include <stdio.h>

namespace Device
{

    Keyboard::Keyboard(::Driver::IKeyboardDriver &_keyboardDriver) : keyboardDriver(_keyboardDriver)
    {
    }

    bool Keyboard::init()
    {
        bool status = keyboardDriver.initialize();
        keyboardDriver.start();
        return status;
    }

    bool Keyboard::tick()
    {
        for (uint8_t i = 0u; i < AmountOfKeys; i++)
        {
            ::Driver::KeyboardKeyIdentifier keyId = static_cast<::Driver::KeyboardKeyIdentifier>(i);
            ::Driver::KeyboardKeyState newState = keyboardDriver.getKeyState(keyId);

            KeyboardKeyActionState currentState = keyActionState[i];
            KeyboardKeyActionState nextState = currentState; // Default to no change

            switch (currentState)
            {
            case KeyboardKeyActionState::PressNot:
                if (newState == Driver::KeyboardKeyState::Pressed)
                {
                    // Key just got pressed
                    pressDurationTicks[i] = 0; // Reset duration counter
                    nextState = KeyboardKeyActionState::PressStart;
                }
                break;

            case KeyboardKeyActionState::PressStart:
                if (newState == Driver::KeyboardKeyState::Pressed)
                {
                    // Key is held down, increment the duration counter
                    pressDurationTicks[i]++;
                }
                else if (newState == Driver::KeyboardKeyState::NotPressed)
                {
                    // Key released, check how long it was pressed
                    if (pressDurationTicks[i] >= LONG_PRESS_THRESHOLD_TICKS)
                    {
                        nextState = KeyboardKeyActionState::PressEndLong;
                    }
                    else
                    {
                        nextState = KeyboardKeyActionState::PressEndShort;
                    }
                }
                break;

            case KeyboardKeyActionState::PressEndShort:
            case KeyboardKeyActionState::PressEndLong:
                // After a short/long press concluded
                if (newState == Driver::KeyboardKeyState::NotPressed)
                {
                    // Go back to PressNot if still not pressed
                    nextState = KeyboardKeyActionState::PressNot;
                }
                else if (newState == Driver::KeyboardKeyState::Pressed)
                {
                    // Key got pressed again
                    pressDurationTicks[i] = 0;
                    nextState = KeyboardKeyActionState::PressStart;
                }
                break;

            default:
                // If there are other states or error conditions, handle them here
                break;
            }

            keyActionState[i] = nextState;
        }

        return true;
    }

    KeyboardKeyActionState Keyboard::getKeyState(::Driver::KeyboardKeyIdentifier key) const
    {
        KeyboardKeyActionState state;

        uint8_t index = static_cast<uint8_t>(key);
        if (index >= AmountOfKeys)
        {
            state = KeyboardKeyActionState::Fail;
        }
        else
        {
            state = keyActionState[index];
        }
        return state;
    }

}
