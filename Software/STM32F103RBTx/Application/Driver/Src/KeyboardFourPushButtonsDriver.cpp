#include "Driver/Inc/KeyboardFourPushButtonsDriver.hpp"
#include "Driver/Inc/KeyboardKeyState.hpp"
#include "Driver/Inc/DriverState.hpp"
#include "Driver/Inc/KeyboardKeyIdentifier.hpp"

#include "main.h" // todo maybe remove
#include "stm32f1xx_hal_gpio.h"

#include <cstdint>

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
            for (auto &key : keyState)
            {
                key.state = getKeyStateFromHW(key.GPIO_Port, key.GPIO_Pin);
            }

            status = true;
        }

        return status;
    }

    KeyboardKeyState KeyboardFourPushButtonsDriver::getKeyState(KeyboardKeyIdentifier key) const
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
                const std::uint8_t id = static_cast<std::uint8_t>(key);
                state = keyState[id].state;
            }
            break;

            case KeyboardKeyIdentifier::LastNotUsed:

            {
                state = KeyboardKeyState::UnknownKeyAsked;
            }
            break;
            }
        }
        else
        {
            state = KeyboardKeyState::DriverNotOperational;
        }

        return state;
    }

    Driver::KeyboardKeyState KeyboardFourPushButtonsDriver::getKeyStateFromHW(GPIO_TypeDef *GPIOx, std::uint16_t GPIO_Pin)
    {
        return (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_SET) ? KeyboardKeyState::Pressed : KeyboardKeyState::NotPressed;
    }
}
