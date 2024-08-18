#include "ST7735DisplayBacklightDriver.hpp"
#include "stm32f1xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

namespace Driver
{

	void ST7735DisplayBacklightDriver::init()
	{
	}

	bool ST7735DisplayBacklightDriver::setBrightness(uint16_t value)
	{

		htim3.Instance = TIM3;
		htim3.Init.Prescaler = 0; // Prescaler value
		htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim3.Init.Period = 7999; // Period value
		htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

		if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
		{
			// Initialization Error
			// Error_Handler();
		}

		// Configure the PWM channel
		TIM_OC_InitTypeDef sConfigOC;
		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		sConfigOC.Pulse = htim3.Init.Period - ((20 * value)); // for fun;  Pulse value for 90% duty cycle
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

		if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
		{
			// Configuration Error
			// Error_Handler();
		}

		// Start PWM signal generation
		if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2) != HAL_OK)
		{
			// PWM Generation Error
			// Error_Handler();
		}
		//*/

		return true;
	}

	uint16_t ST7735DisplayBacklightDriver::getBrightness()
	{
		return brightness;
	}

}
