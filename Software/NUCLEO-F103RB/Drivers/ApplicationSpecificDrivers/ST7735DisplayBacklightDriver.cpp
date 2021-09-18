#include "ST7735DisplayBacklightDriver.h"
#include "stm32f1xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

namespace Driver
{

void ST7735DisplayBacklightDriver::init()
{
}

void ST7735DisplayBacklightDriver::setBrightness(uint16_t value)
{
	brightness = value;

		value *=100;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, value);
/*
	   TIM_OC_InitTypeDef sConfigOC;

	    sConfigOC.OCMode = TIM_OCMODE_PWM1;
	    htim3.Init.Period = 500;
	    sConfigOC.Pulse = value;
	    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
	    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
*/
}

uint16_t ST7735DisplayBacklightDriver::getBrightness()
{
	return brightness;
}

}
