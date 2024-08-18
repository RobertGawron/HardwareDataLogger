#ifndef IAMBIENTLIGHTSENSORDRIVER_H_
#define IAMBIENTLIGHTSENSORDRIVER_H_

#include <stdint.h>

namespace Driver
{

class IAmbientLightSensorDriver
{
public:
	virtual ~IAmbientLightSensorDriver() = default;

	virtual bool init() = 0;
	virtual uint32_t getAmbientLightLevel() = 0;
};

}

#endif
