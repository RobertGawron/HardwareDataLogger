#include "DisplayBacklightDriver.h"
#include "stm32f1xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

namespace Driver
{

DisplayBacklightDriver::DisplayBacklightDriver() : brightness(0)
{
}

DisplayBacklightDriver::~DisplayBacklightDriver()
{
}

void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,
uint16_t pulse)
{
 HAL_TIM_PWM_Stop(&timer, channel); // stop generation of pwm
 TIM_OC_InitTypeDef sConfigOC;
 timer.Init.Period = period; // set the period duration
 HAL_TIM_PWM_Init(&timer); // reinititialise with new period value
 sConfigOC.OCMode = TIM_OCMODE_PWM1;
 sConfigOC.Pulse = pulse; // set the pulse duration
 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
 HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
 HAL_TIM_PWM_Start(&timer, channel); // start pwm generation
}

void DisplayBacklightDriver::init()
{

	//setPWM(htim3, TIM_CHANNEL_2, 255, 5);
	/*
    TIM_OC_InitTypeDef sConfigOC;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 5;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);


	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
*/
	// this wis very crude way to verify if "PWM" from GPPIO can be used directly to change backlight level of LCD
//	HAL_GPIO_WritePin(BACKGROUND_LIGHT_SENSOR_GPIO_Port,
	//		BACKGROUND_LIGHT_SENSOR_Pin, GPIO_PIN_SET);
	//  HAL_Delay (1);
	//  HAL_GPIO_WritePin(BACKGROUND_LIGHT_SENSOR_GPIO_Port, BACKGROUND_LIGHT_SENSOR_Pin, GPIO_PIN_RESET);
	//  HAL_Delay (20);
}

void DisplayBacklightDriver::setBrightness(int value)
{
	brightness = value;

	uint16_t period = 255;
	uint16_t pulse = value;

	 HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2); // stop generation of pwm
	 TIM_OC_InitTypeDef sConfigOC;
	 htim3.Init.Period = period; // set the period duration
	 HAL_TIM_PWM_Init(&htim3); // reinititialise with new period value
	 sConfigOC.OCMode = TIM_OCMODE_PWM1;
	 sConfigOC.Pulse = pulse; // set the pulse duration
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	 HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
	 HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // start pwm generation
}

int DisplayBacklightDriver::getBrightness()
{
	return brightness;
}

}
