#include "AmbientLightSensorDriver.hpp"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;

namespace Driver
{
	bool AmbientLightSensorDriver::init()
	{
		return true;
	}

	uint32_t AmbientLightSensorDriver::getAmbientLightLevel()
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
