module;

#include "stm32f1xx_hal.h"

#include <cstdint>

export module Driver.BrightnessDriver;

import Driver.DriverComponent;
import Driver.BrightnessDriverConcept;

export namespace Driver
{
    /**
     * @class BrightnessDriver
     * @brief LCD backlight brightness control using a hardware PWM timer.
     *
     * @details
     * This driver starts/stops PWM output on a pre-configured timer channel and
     * updates the duty cycle to set perceived backlight brightness.
     *
     * @note The timer peripheral and its GPIO pin (alternate-function output) must be
     * initialized by platform code (e.g. CubeMX `MX_TIMx_Init()` / `HAL_TIM_MspPostInit()`)
     * before calling onStart().
     */
    class BrightnessDriver final : public DriverComponent
    {
    public:
        /**
         * @brief Construct a brightness driver bound to a HAL timer handle.
         * @param timer HAL timer handle configured for PWM (e.g. TIM3).
         */
        explicit constexpr BrightnessDriver(TIM_HandleTypeDef &timer) noexcept
            : timer(timer)
        {
        }

        ~BrightnessDriver() = default;

        BrightnessDriver() = delete;
        BrightnessDriver(const BrightnessDriver &) = delete;
        BrightnessDriver &operator=(const BrightnessDriver &) = delete;
        BrightnessDriver(BrightnessDriver &&) = delete;
        BrightnessDriver &operator=(BrightnessDriver &&) = delete;

        /**
         * @brief Set backlight brightness.
         * @param brightness Brightness level in the driver-defined range (typically 0..MAX_BRIGHTNESS).
         * @return true on valid input and successful compare update; false on invalid level.
         *
         * @note This updates the PWM duty cycle. PWM must be started via onStart() to take effect.
         */
        [[nodiscard]] bool setBrightness(std::uint8_t percentage) noexcept;

        /**
         * @brief Driver initialization hook.
         * @return Always true (timer/GPIO initialization is handled externally).
         */
        [[nodiscard]] constexpr bool onInit() noexcept { return true; }

        /**
         * @brief Start PWM output and apply the initial brightness level.
         * @return true on success; false if HAL PWM start fails.
         */
        [[nodiscard]] bool onStart() noexcept;

        /**
         * @brief Stop PWM output (backlight control disabled).
         * @return true on success; false if HAL PWM stop fails.
         */
        [[nodiscard]] bool onStop() noexcept;

    private:
        /**
         * @brief Start PWM generation on the configured timer channel.
         */
        [[nodiscard]] bool startPwm() noexcept;

        /**
         * @brief Stop PWM generation on the configured timer channel.
         */
        [[nodiscard]] bool stopPwm() noexcept;

        /// HAL timer used to generate the PWM signal.
        TIM_HandleTypeDef &timer;
    };

    static_assert(Driver::Concepts::BrightnessDriverConcept<BrightnessDriver>,
                  "BrightnessDriver must satisfy concept requirements");

} // namespace Driver