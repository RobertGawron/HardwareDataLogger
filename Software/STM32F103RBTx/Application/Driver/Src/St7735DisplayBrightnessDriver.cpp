#include "Driver/Inc/St7735DisplayBrightnessDriver.hpp"

#include <cstdint>
#include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal_def.h"

namespace Driver
{
    St7735DisplayBrightnessDriver::St7735DisplayBrightnessDriver(TIM_HandleTypeDef &_htim) : htim(_htim)
    {
    }

    bool St7735DisplayBrightnessDriver::onInitialize()
    {
        bool status = false;

        if (initializeTimer() &&
            configurePWMChannel())
        {
            status = true;
        }

        return status;
    }

    bool St7735DisplayBrightnessDriver::onStart()
    {
        const bool status = startPWMWithInitialBrightness();

        return status;
    }

    bool St7735DisplayBrightnessDriver::onStop()
    {
        const bool status = stopPWM();

        // Optionally, additional hardware deinitialization can be done here if necessary
        // For example, disable the clock to save power if no other peripherals need it
        // __HAL_RCC_TIM3_CLK_DISABLE();

        return status;
    }

    bool St7735DisplayBrightnessDriver::onReset()
    {
        return true;
    }

    bool St7735DisplayBrightnessDriver::setBrightness(std::uint8_t brightness)
    {
        bool status = false;

        if (brightness <= MaxBrightness)
        {
            // Calculate the pulse length
            const std::uint32_t pulse = calculatePulseFromBrightness(brightness);

            // Set the pulse value for the PWM channel
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, pulse);

            status = true;
        }

        return status;
    }

    bool St7735DisplayBrightnessDriver::initializeTimer()
    {
        bool status = true;

        // Enable the clock for TIM3
        __HAL_RCC_TIM3_CLK_ENABLE();

        constexpr std::uint32_t TIMER_CLOCK_FREQ = 24000000; // Timer clock frequency in Hz
        constexpr std::uint32_t PWM_FREQ = 5000;             // Desired PWM frequency in Hz
        constexpr std::uint32_t TIMER_PERIOD = (TIMER_CLOCK_FREQ / PWM_FREQ) - 1;

        htim.Instance = TIM3;    // This should be configurable.
        htim.Init.Prescaler = 0; // No prescaler, timer clock remains 24 MHz
        htim.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim.Init.Period = TIMER_PERIOD; // Period to get a PWM frequency of 5 kHz
        htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

        if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
        {
            // Initialization Error
            // Error_Handler();
            status = false;
        }

        return status;
    }

    bool St7735DisplayBrightnessDriver::configurePWMChannel()
    {
        bool status = true;

        // Configure the PWM channel
        TIM_OC_InitTypeDef sConfigOC;
        sConfigOC.OCMode = TIM_OCMODE_PWM1;
        sConfigOC.Pulse = 0; // Initial duty cycle 0%
        sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

        if (HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
        {
            // Configuration Error
            // Error_Handler();
            status = false;
        }

        return status;
    }

    bool St7735DisplayBrightnessDriver::startPWMWithInitialBrightness()
    {
        bool status = true;

        // Start PWM on Channel 2
        if (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_2) != HAL_OK)
        {
            // PWM Generation Error
            // Error_Handler();
            status = false;
        }

        // Set the initial brightness
        const std::uint32_t pulse = calculatePulseFromBrightness(initialBrightness); // Calculate pulse based on initial brightness (0-100%)
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, pulse);                          // Set duty cycle based on brightness

        return status;
    }

    bool St7735DisplayBrightnessDriver::stopPWM()
    {
        bool status = true;

        // Stop the PWM used for backlight control
        if (HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_2) != HAL_OK)
        {
            status = false;
        }

        return status;
    }

    std::uint32_t St7735DisplayBrightnessDriver::calculatePulseFromBrightness(BrightnessPercentage brightness)
    {
        // Calculate the pulse length based on brightness (0-100%)
        const std::uint32_t pulse = (brightness * 4799) / 100;
        return pulse;
    }

}
