#include "AmbientLightSensorDriver.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;

namespace Driver
{

AmbientLightSensorDriver::AmbientLightSensorDriver()
{
}

AmbientLightSensorDriver::~AmbientLightSensorDriver()
{
}

void AmbientLightSensorDriver::init()
{
}

uint32_t AmbientLightSensorDriver::getAmbientLight()
{
	volatile uint32_t adcResult;

	// don't bother with DMA at this point
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	adcResult = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	return adcResult;
}
}
