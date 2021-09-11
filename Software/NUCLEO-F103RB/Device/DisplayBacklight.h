#ifndef DISPLAYBACKLIGHT_H_
#define DISPLAYBACKLIGHT_H_

#include "AmbientLightSensorDriver.h"
#include "DisplayBacklightDriver.h"

namespace Device
{

class DisplayBacklight
{
public:
	DisplayBacklight();
	virtual ~DisplayBacklight();
	void tick();
private:
	Driver::AmbientLightSensorDriver mAmbientLightSensorDriver;
	Driver::DisplayBacklightDriver mDisplayBacklightDriver;
};

}

#endif
