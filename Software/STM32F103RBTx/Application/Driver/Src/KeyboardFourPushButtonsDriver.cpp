#include "Driver/Inc/KeyboardFourPushButtonsDriver.hpp"
#include "Driver/Inc/KeyboardKeyState.hpp"
#include "Driver/Inc/DriverState.hpp"
#include "Driver/Inc/KeyboardKeyIdentifier.hpp"

#include "stm32f1xx_hal_gpio.h"

#include <cstdint>
#include <algorithm> // for std::find_if

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
            // Use range-based for loop for clarity and simplicity
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
        // Initialize the result with a default state
        KeyboardKeyState result = KeyboardKeyState::UnknownKeyAsked;

        if (isInState(DriverState::State::Running))
        {
            // Use std::find_if to locate the key configuration in the array
            // The std::find_if function returns an iterator, which is an object (not a raw pointer) in modern STL containers.
            // codechecker_suppress [readability-qualified-auto]
            auto it = std::find_if(
                keyState.begin(),
                keyState.end(),
                [this, key](const KeyState &ks)
                {
                    return static_cast<KeyboardKeyIdentifier>(&ks - keyState.data()) == key;
                });

            if (it != keyState.end())
            {
                result = it->state;
            }
            else if (key == KeyboardKeyIdentifier::LastNotUsed)
            {
                result = KeyboardKeyState::UnknownKeyAsked;
            }
        }
        else
        {
            result = KeyboardKeyState::DriverNotOperational;
        }

        return result;
    }

    Driver::KeyboardKeyState KeyboardFourPushButtonsDriver::getKeyStateFromHW(GPIO_TypeDef *GPIOx, std::uint16_t GPIO_Pin)
    {
        return (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_SET) ? KeyboardKeyState::Pressed : KeyboardKeyState::NotPressed;
    }
}
