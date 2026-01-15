module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_tim.h"

#include <cstdint>

module Driver.BrightnessDriver;

namespace Driver
{
    BrightnessDriver::BrightnessDriver(TIM_HandleTypeDef &_htim) noexcept
        : htim(_htim)
    {
    }

    bool BrightnessDriver::onInit() noexcept
    {
        return initializeTimer() && configurePwmChannel();
    }

    bool BrightnessDriver::onStart() noexcept
    {
        return startPwmWithInitialBrightness();
    }

    bool BrightnessDriver::onStop() noexcept
    {
        return stopPwm();
    }

    bool BrightnessDriver::setBrightness(std::uint8_t brightness) noexcept
    {
        bool status = false;

        if (brightness <= MAX_BRIGHTNESS) [[likely]]
        {
            const auto pulse = calculatePulseFromBrightness(brightness);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, pulse);
            status = true;
        }

        return status;
    }

    bool BrightnessDriver::initializeTimer() noexcept
    {
        __HAL_RCC_TIM3_CLK_ENABLE();

        htim.Instance = TIM3;
        htim.Init.Prescaler = 0U;
        htim.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim.Init.Period = TIMER_PERIOD;
        htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

        return HAL_TIM_PWM_Init(&htim) == HAL_OK;
    }

    bool BrightnessDriver::configurePwmChannel() noexcept
    {
        TIM_OC_InitTypeDef sConfigOC{};
        sConfigOC.OCMode = TIM_OCMODE_PWM1;
        sConfigOC.Pulse = 0U;
        sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

        return HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_2) == HAL_OK;
    }

    bool BrightnessDriver::startPwmWithInitialBrightness() noexcept
    {
        bool status = (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_2) == HAL_OK);

        if (status)
        {
            const auto pulse = calculatePulseFromBrightness(INITIAL_BRIGHTNESS);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, pulse);
        }

        return status;
    }

    bool BrightnessDriver::stopPwm() noexcept
    {
        return HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_2) == HAL_OK;
    }

} // namespace Driver