#ifndef AMBIENTLIGHTSENSORDRIVER_H_
#define AMBIENTLIGHTSENSORDRIVER_H_

#include <stdint.h>

namespace Driver
{

class IAmbientLightSensorDriver
{
public:
	virtual ~IAmbientLightSensorDriver() = default;

	virtual void init() = 0;
	virtual uint32_t getAmbientLightLevel() = 0;
};

}

#endif
