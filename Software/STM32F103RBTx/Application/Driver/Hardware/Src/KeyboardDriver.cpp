/**
 * @file KeyboardDriver.cpp
 * @brief Implementation of modern GPIO keyboard driver
 */

#include "Driver/Hardware/Inc/KeyboardDriver.hpp"
#include "Driver/Interface/KeyState.hpp"
#include "Driver/Interface/DriverComponent.hpp"

#include <cstddef>

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

    KeyState KeyboardDriver::getKeyState(KeyIdentifier key) const noexcept
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