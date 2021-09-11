#include "DisplayBacklight.h"

namespace Device
{

DisplayBacklight::DisplayBacklight()
{
}

DisplayBacklight::~DisplayBacklight()
{
}

void DisplayBacklight::tick()
{
	mAmbientLightSensorDriver.tick();
	mDisplayBacklightDriver.tick();
}

}
