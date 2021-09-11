#ifndef AMBIENTLIGHTSENSORDRIVER_H_
#define AMBIENTLIGHTSENSORDRIVER_H_

namespace Driver
{

class AmbientLightSensorDriver
{
public:
	AmbientLightSensorDriver();
	virtual ~AmbientLightSensorDriver();
	void tick();
};

}

#endif
