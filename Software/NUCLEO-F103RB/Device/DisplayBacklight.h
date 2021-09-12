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
	void init();
	void tick();
	void setBrightness(int value);

	// TODO this is crap!!!!
	int getRawADCBrightness();
	int getRawPWMBrightness();

private:
	Driver::AmbientLightSensorDriver mAmbientLightSensorDriver;
	Driver::DisplayBacklightDriver mDisplayBacklightDriver;
};

}

#endif
