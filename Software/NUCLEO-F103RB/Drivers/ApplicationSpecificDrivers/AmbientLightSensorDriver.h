#ifndef AMBIENTLIGHTSENSORDRIVER_H_
#define AMBIENTLIGHTSENSORDRIVER_H_

#include "stm32f1xx_hal.h"

namespace Driver
{

class AmbientLightSensorDriver
{
public:
	AmbientLightSensorDriver();
	virtual ~AmbientLightSensorDriver();
	void init();
	uint32_t getAmbientLight();
};

}

#endif
