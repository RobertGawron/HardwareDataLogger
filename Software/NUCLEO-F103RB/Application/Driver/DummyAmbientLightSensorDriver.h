#ifndef DUMMYAMBIENTLIGHTSENSORDRIVER_H_
#define DUMMYAMBIENTLIGHTSENSORDRIVER_H_

#include <stdint.h>
#include "IAmbientLightSensorDriver.h"

namespace Driver
{

class DummyAmbientLightSensorDriver: public IAmbientLightSensorDriver
{
public:
	DummyAmbientLightSensorDriver() = default;
	virtual ~DummyAmbientLightSensorDriver() = default;

	void init();
	uint32_t getAmbientLightLevel();
};

}

#endif
