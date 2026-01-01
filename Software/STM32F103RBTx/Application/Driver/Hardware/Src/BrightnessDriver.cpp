module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

#include <cstdint>

module Driver.BrightnessDriver;

namespace Driver
{
    namespace
    {
        constexpr std::uint32_t PWM_CHANNEL = TIM_CHANNEL_3; // todo pass as an arg in constructor
        constexpr std::uint8_t MAX_BRIGHTNESS = 100U;
        constexpr std::uint8_t INITIAL_BRIGHTNESS = 50U;

        [[nodiscard]] inline std::uint32_t pulseFromBrightness(
            const TIM_HandleTypeDef &t,
            std::uint8_t brightness) noexcept
        {
            const std::uint32_t arr = t.Instance->ARR; // ARR (auto-reload)
            return (static_cast<std::uint32_t>(brightness) * arr) / MAX_BRIGHTNESS;
        }
    }

    bool BrightnessDriver::onStart() noexcept
    {
        bool status = false;

        if (HAL_TIM_PWM_Start(&timer, PWM_CHANNEL) == HAL_OK)
        {
            status = setBrightness(INITIAL_BRIGHTNESS);
        }

        return status;
    }

    bool BrightnessDriver::onStop() noexcept
    {
        return (HAL_TIM_PWM_Stop(&timer, PWM_CHANNEL) == HAL_OK);
    }

    bool BrightnessDriver::setBrightness(std::uint8_t brightness) noexcept
    {
        bool status = false;

        if (brightness <= MAX_BRIGHTNESS)
        {
            const std::uint32_t pulse = pulseFromBrightness(timer, brightness);
            __HAL_TIM_SET_COMPARE(&timer, PWM_CHANNEL, pulse);
            status = true;
        }

        return status;
    }

} // namespace Driver