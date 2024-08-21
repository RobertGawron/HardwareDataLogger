#include "Keyboard.hpp"
#include "KeyboardKeyState.hpp"
#include "KeyboardKeyActionState.hpp"

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
        keyboardDriver.tick();

        for (uint8_t i = 0u; i < AmountOfKeys; i++)
        {
            ::Driver::KeyboardKeyIdentifier keyId = static_cast<::Driver::KeyboardKeyIdentifier>(i);
            ::Driver::KeyboardKeyState newState = keyboardDriver.getKeyState(keyId);

            KeyboardKeyActionState stateToSet = KeyboardKeyActionState::PressNot;

            switch (keyActionState[i])
            {
            case KeyboardKeyActionState::PressNot:
            {
                // user ended pressing the button
                if (newState == Driver::KeyboardKeyState::Pressed)
                {
                    stateToSet = KeyboardKeyActionState::PressStart;
                }
            }
            break;

            case KeyboardKeyActionState::PressStart:
            {
                // user ended pressing the button
                if (newState == Driver::KeyboardKeyState::NotPressed)
                {
                    stateToSet = KeyboardKeyActionState::PressEndShort;
                }
            }
            break;

            case KeyboardKeyActionState::PressEndShort:
            {
                // user ended pressing the button
                if (newState == Driver::KeyboardKeyState::NotPressed)
                {
                    stateToSet = KeyboardKeyActionState::PressNot;
                }
            }
            break;

            default:
                break;
            }

            keyActionState[i] = stateToSet;
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
