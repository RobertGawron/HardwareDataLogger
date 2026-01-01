module;
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_ll_gpio.h"
#include "main.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <string_view>

module Driver.KeyboardDriver;

import Driver.DriverComponent;
import Driver.KeyState;
import Driver.KeyId;

#define DRIVER_STR_IMPL(x) #x
#define DRIVER_STR(x) DRIVER_STR_IMPL(x)

namespace
{
    static constexpr std::size_t KEY_COUNT =
        static_cast<std::size_t>(std::to_underlying(Driver::KeyId::LAST_NOT_USED));

    // Compile-time mapping from key identifier to pin mask.
    static constexpr std::array<std::uint16_t, KEY_COUNT> keyPinMask{
        // values are from CubeMX generated main.h
        KEY_UP_Pin,
        KEY_DOWN_Pin,
        KEY_LEFT_Pin,
        KEY_RIGHT_Pin,
    };

    // Ensures KeyId values match the expected contiguous ordering.
    static_assert(std::to_underlying(Driver::KeyId::UP) == 0U,
                  "KeyId::Up must remain 0 to match keyPinMask content");

    //  Ensures KeyId values match the expected contiguous ordering.
    static_assert(std::to_underlying(Driver::KeyId::DOWN) == 1U,
                  "KeyId::Down must remain 1 to match keyPinMask content");

    // Ensures KeyId values match the expected contiguous ordering.
    static_assert(std::to_underlying(Driver::KeyId::LEFT) == 2U,
                  "KeyId::Left must remain 2 to match keyPinMask content");

    // Ensures KeyId values match the expected contiguous ordering.
    static_assert(std::to_underlying(Driver::KeyId::RIGHT) == 3U,
                  "KeyId::Right must remain 3 to match keyPinMask content");

    static constexpr std::string_view KEY_UP_PORT = DRIVER_STR(KEY_UP_GPIO_Port);
    static constexpr std::string_view KEY_DOWN_PORT = DRIVER_STR(KEY_DOWN_GPIO_Port);
    static constexpr std::string_view KEY_RIGHT_PORT = DRIVER_STR(KEY_RIGHT_GPIO_Port);
    static constexpr std::string_view KEY_LEFT_PORT = DRIVER_STR(KEY_LEFT_GPIO_Port);

    static_assert(KEY_UP_PORT == KEY_LEFT_PORT,
                  "All keys must be on the same port");

    static_assert(KEY_DOWN_PORT == KEY_LEFT_PORT,
                  "All keys must be on the same port");

    static_assert(KEY_RIGHT_PORT == KEY_LEFT_PORT,
                  "All keys must be on the same port");
}
namespace Driver
{
    bool KeyboardDriver::tick() noexcept
    {
        // Driver operational-state transitions are handled by the DriverComponent base class.
        // If we are here the driver is already in running state

        // Checked at the beginning of the file that all keys are on the same port.
        GPIO_TypeDef *GPIO_PORT = KEY_UP_GPIO_Port;

        // Read once; individual key states are derived from this cached snapshot.
        gpioSnapshot = LL_GPIO_ReadInputPort(GPIO_PORT);

        return true;
    }

    KeyState KeyboardDriver::getKeyState(KeyId key) const noexcept
    {
        KeyState status = KeyState::DriverNotOperational;

        if (getState() == DriverComponent::State::RUNNING)
        {
            status = KeyState::UnknownKeyAsked;

            if (Driver::isValid(key))
            {
                const std::size_t index =
                    static_cast<std::size_t>(std::to_underlying(key));

                const std::uint32_t pinMask =
                    static_cast<std::uint32_t>(keyPinMask[index]);

                // Active-low: pressed when the input bit is 0.
                status = (gpioSnapshot & pinMask) ? KeyState::NotPressed
                                                  : KeyState::Pressed;
            }
        }

        return status;
    }

} // namespace Driver