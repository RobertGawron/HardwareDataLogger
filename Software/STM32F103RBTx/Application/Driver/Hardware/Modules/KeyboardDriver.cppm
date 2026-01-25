module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "main.h"

#include <array>
#include <cstdint>
#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <span>
#include <utility>
#include <limits>

export module Driver.KeyboardDriver;

import Driver.DriverComponent;
import Driver.KeyboardDriverConcept;
import Driver.KeyState;
import Driver.KeyId;

export namespace Driver
{
    /**
     * @class KeyboardDriver
     * @brief Zero-overhead GPIO button reader with compile-time configuration
     *
     * Reads four push buttons via GPIO. No hardware debouncing or external pull-ups required
     * (pull-ups configured in CubeMX). Debouncing handled at higher level if needed.
     */
    class KeyboardDriver final : public DriverComponent
    {
    public:
        static constexpr std::uint8_t AMOUNT_OF_KEYS =
            std::to_underlying(KeyId::LastNotUsed);

        KeyboardDriver() = default;
        ~KeyboardDriver() = default;

        KeyboardDriver(const KeyboardDriver &) = delete;
        KeyboardDriver &operator=(const KeyboardDriver &) = delete;
        KeyboardDriver(KeyboardDriver &&) = delete;
        KeyboardDriver &operator=(KeyboardDriver &&) = delete;

        [[nodiscard]] bool tick() noexcept;
        [[nodiscard]] KeyState getKeyState(KeyId key) const noexcept;

    protected:
        // [[nodiscard]] constexpr bool onInit() noexcept  { return true; }
        //  [[nodiscard]] constexpr bool onStart() noexcept  { return true; }
        //  [[nodiscard]] constexpr bool onStop() noexcept  { return true; }

    private:
        /**
         * @brief GPIO pin configuration for a single key
         */
        struct KeyConfig
        {
            KeyState state;
            GPIO_TypeDef *port;
            std::uint16_t pin;

            constexpr KeyConfig(GPIO_TypeDef *p, std::uint16_t pin_num) noexcept
                : state(KeyState::NotPressed), port(p), pin(pin_num)
            {
            }
        };

        /**
         * @brief Reads current GPIO state
         * @return KeyState::Pressed if pin is low (button pressed), NotPressed otherwise
         */
        [[nodiscard]] static KeyState readGpio(GPIO_TypeDef *port, std::uint16_t pin) noexcept;

        std::array<KeyConfig, AMOUNT_OF_KEYS> keys = {{{KEY_UP_GPIO_Port, KEY_UP_Pin},
                                                       {KEY_DOWN_GPIO_Port, KEY_DOWN_Pin},
                                                       {KEY_LEFT_GPIO_Port, KEY_LEFT_Pin},
                                                       {KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin}}};
    };

    static_assert(Driver::Concepts::KeyboardDriverConcept<KeyboardDriver>,
                  "KeyboardDriver must satisfy concept requirements");

} // namespace Driver