module;
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "main.h"

#include <cstddef>
#include <cstdint>

module Driver.KeyboardDriver;

import Driver.DriverComponent;
import Driver.KeyState;

namespace Driver
{
    bool KeyboardDriver::tick() noexcept
    {
        bool status = false;

        if (getState() == DriverComponent::State::RUNNING)
        {
            // Update all key states from GPIO
            for (auto &key : keys)
            {
                key.state = readGpio(key.port, key.pin);
            }
            status = true;
        }

        return status;
    }

    KeyState KeyboardDriver::getKeyState(KeyId key) const noexcept
    {
        const auto index = static_cast<std::size_t>(key);

        if (index >= keys.size()) [[unlikely]]
        {
            return KeyState::UnknownKeyAsked;
        }

        if (getState() != DriverComponent::State::RUNNING) [[unlikely]]
        {
            return KeyState::DriverNotOperational;
        }

        return keys[index].state;
    }

    KeyState KeyboardDriver::readGpio(GPIO_TypeDef *port, std::uint16_t pin) noexcept
    {
        // Button pressed when GPIO is low (active low with pull-up)
        const auto pinState = HAL_GPIO_ReadPin(port, pin);
        return (pinState == GPIO_PIN_RESET) ? KeyState::Pressed : KeyState::NotPressed;
    }

} // namespace Driver