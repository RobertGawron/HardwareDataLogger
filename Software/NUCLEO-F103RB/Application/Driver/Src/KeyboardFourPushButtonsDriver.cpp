#include "KeyboardFourPushButtonsDriver.hpp"
#include "main.h"

namespace Driver
{
    bool KeyboardFourPushButtonsDriver::onInitialize()
    {
        // Do nothing, this driver just reads data from GPIO, no need for particular action.
        return true;
    }

    bool KeyboardFourPushButtonsDriver::onStart()
    {
        // Do nothing, this driver just reads data from GPIO, no need for particular action.
        return true;
    }

    bool KeyboardFourPushButtonsDriver::onStop()
    {
        // Do nothing, this driver just reads data from GPIO, no need for particular action.
        return true;
    }

    bool KeyboardFourPushButtonsDriver::onReset()
    {
        // Do nothing, this driver just reads data from GPIO, no need for particular action.
        return true;
    }

    bool KeyboardFourPushButtonsDriver::tick()
    {
        bool status = false;

        if (isInState(DriverState::State::Running))
        {
            for (uint8_t i = 0u; i < AmountOfKeys; i++)
            {
                keyState[i].state = getKeyStateFromHW(keyState[i].GPIO_Port, keyState[i].GPIO_Pin);
            }

            status = true;
        }

        return status;
    }

    KeyboardKeyState KeyboardFourPushButtonsDriver::getKeyState(const KeyboardKeyIdentifier key) const
    {
        KeyboardKeyState state;

        if (isInState(DriverState::State::Running))
        {
            switch (key)
            {
            case KeyboardKeyIdentifier::Up:
            case KeyboardKeyIdentifier::Down:
            case KeyboardKeyIdentifier::Left:
            case KeyboardKeyIdentifier::Right:
            {
                const uint8_t id = static_cast<uint8_t>(key);
                state = keyState[id].state;
            }
            break;

            default:
                state = KeyboardKeyState::UnknownKeyAsked;
                break;
            };
        }
        else
        {
            state = KeyboardKeyState::DriverNotOperational;
        }

        return state;
    }

    Driver::KeyboardKeyState KeyboardFourPushButtonsDriver::getKeyStateFromHW(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) const
    {
        return (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_SET) ? KeyboardKeyState::Pressed : KeyboardKeyState::NotPressed;
    }
}
