#include "DisplayBacklight.h"

namespace Device
{

DisplayBacklight::DisplayBacklight()
{
}

DisplayBacklight::~DisplayBacklight()
{
}

void DisplayBacklight::init()
{
	mDisplayBacklightDriver.init();
}

void DisplayBacklight::tick()
{
	//mAmbientLightSensorDriver.getAmbientLight();
	//mDisplayBacklightDriver.tick();
}

void DisplayBacklight::setBrightness(int value)
{
	// todo check
	mDisplayBacklightDriver.setBrightness(value);
}

// TODO this is crap!!!!
int DisplayBacklight::getRawADCBrightness()
{
	return mAmbientLightSensorDriver.getAmbientLight();
}

int DisplayBacklight::getRawPWMBrightness()
{
	return mDisplayBacklightDriver.getBrightness();
}

}
