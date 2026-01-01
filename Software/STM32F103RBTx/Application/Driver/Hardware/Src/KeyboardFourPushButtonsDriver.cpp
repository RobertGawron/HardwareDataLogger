#include "Driver/Hardware/Inc/KeyboardFourPushButtonsDriver.hpp"
#include "Driver/Interface/KeyState.hpp"
#include "Driver/Interface/DriverState.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"

#include "stm32f1xx_hal_gpio.h"

#include <cstdint>
#include <algorithm>

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
                key.state = readGpioState(key.GPIO_Port, key.GPIO_Pin);
            }

            status = true;
        }

        return status;
    }

    Driver::KeyState KeyboardFourPushButtonsDriver::getKeyState(KeyIdentifier key) const
    {
        Driver::KeyState result = Driver::KeyState::UnknownKeyAsked;

        if (isInState(DriverState::State::Running))
        {
            const auto *const iterator = std::find_if(
                keyState.begin(),
                keyState.end(),
                [key, this](const KeyConfig &keyConfig) noexcept
                {
                    return static_cast<KeyIdentifier>(&keyConfig - keyState.data()) == key;
                });

            if (iterator != keyState.end())
            {
                result = iterator->state;
            }
        }
        else
        {
            result = Driver::KeyState::DriverNotOperational;
        }

        return result;
    }

    Driver::KeyState KeyboardFourPushButtonsDriver::readGpioState(GPIO_TypeDef *GPIOx, std::uint16_t GPIO_Pin)
    {
        Driver::KeyState result = Driver::KeyState::NotPressed;

        if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_SET)
        {
            result = Driver::KeyState::Pressed;
        }

        return result;
    }
}
