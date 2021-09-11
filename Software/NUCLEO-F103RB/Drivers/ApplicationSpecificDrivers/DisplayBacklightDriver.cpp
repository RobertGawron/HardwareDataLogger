#include "DisplayBacklightDriver.h"
#include "stm32f1xx_hal.h"
#include "main.h"
namespace Driver
{

DisplayBacklightDriver::DisplayBacklightDriver()
{
}

DisplayBacklightDriver::~DisplayBacklightDriver()
{
}

void DisplayBacklightDriver::tick()
{
	  // this wis very crude way to verify if "PWM" from GPPIO can be used directly to change backlight level of LCD
	  HAL_GPIO_WritePin(BACKGROUND_LIGHT_SENSOR_GPIO_Port, BACKGROUND_LIGHT_SENSOR_Pin, GPIO_PIN_SET);
	  HAL_Delay (1);
	  HAL_GPIO_WritePin(BACKGROUND_LIGHT_SENSOR_GPIO_Port, BACKGROUND_LIGHT_SENSOR_Pin, GPIO_PIN_RESET);
	  HAL_Delay (20);
}
}
