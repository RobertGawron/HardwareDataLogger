module;
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_ll_gpio.h"
#include "main.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <utility> // std::to_underlying

module Driver.KeyboardDriver;

import Driver.DriverComponent;
import Driver.KeyState;
import Driver.KeyId;

namespace
{

    /**
     * @brief Number of keys supported by this driver.
     *
     * This value is derived from the @ref Driver::KeyId sentinel enumerator and is used
     * for bounds checks and compile-time sizing.
     */
    static constexpr std::size_t KEY_COUNT =
        static_cast<std::size_t>(std::to_underlying(Driver::KeyId::LastNotUsed));

    /// Compile-time mapping from key identifier to pin mask.
    static constexpr std::array<std::uint16_t, KEY_COUNT> keyPinMask{
        // values are from CubeMX generated main.h
        KEY_UP_Pin,
        KEY_DOWN_Pin,
        KEY_LEFT_Pin,
        KEY_RIGHT_Pin,
    };

    // ---------------------------------------------------------------------
    // Compile-time consistency checks
    // ---------------------------------------------------------------------

    /** @brief Ensures KeyId values match the expected contiguous ordering. */
    static_assert(std::to_underlying(Driver::KeyId::Up) == 0U,
                  "KeyId::Up must remain 0 to match keyPinMask content");

    /** @brief Ensures KeyId values match the expected contiguous ordering. */
    static_assert(std::to_underlying(Driver::KeyId::Down) == 1U,
                  "KeyId::Down must remain 1 to match keyPinMask content");

    /** @brief Ensures KeyId values match the expected contiguous ordering. */
    static_assert(std::to_underlying(Driver::KeyId::Left) == 2U,
                  "KeyId::Left must remain 2 to match keyPinMask content");

    /** @brief Ensures KeyId values match the expected contiguous ordering. */
    static_assert(std::to_underlying(Driver::KeyId::Right) == 3U,
                  "KeyId::Right must remain 3 to match keyPinMask content");
#if 0
        /** @brief Ensures the pin mapping table stays consistent with KEY_COUNT. */
        static_assert(keyPinMask.size() == KEY_COUNT,
                      "Pin mapping table size must match the number of keys");

        /** @brief Ensures the build-time configuration places all keys on the supported port. */
        static_assert(reinterpret_cast<std::uintptr_t>(KEY_UP_GPIO_Port) == GPIOC_BASE,
                      "Key configuration mismatch: KEY_UP must be on GPIOC");

        /** @brief Ensures the build-time configuration places all keys on the supported port. */
        static_assert(KEY_DOWN_GPIO_Port == GPIOC,
                      "Key configuration mismatch: KEY_DOWN must be on GPIOC");

        /** @brief Ensures the build-time configuration places all keys on the supported port. */
        static_assert(KEY_LEFT_GPIO_Port == GPIOC,
                      "Key configuration mismatch: KEY_LEFT must be on GPIOC");

        /** @brief Ensures the build-time configuration places all keys on the supported port. */
        static_assert(KEY_RIGHT_GPIO_Port == GPIOC,
                      "Key configuration mismatch: KEY_RIGHT must be on GPIOC");
#endif
}
namespace Driver
{
    bool KeyboardDriver::tick() noexcept
    {
        // Driver operational-state transitions are handled by the DriverComponent base class.
        // If we are here the driver is already in running state

        // Read once; individual key states are derived from this cached snapshot.
        gpioSnapshot = LL_GPIO_ReadInputPort(GPIOC);

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