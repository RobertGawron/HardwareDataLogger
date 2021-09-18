#include "DisplayBacklight.h"

namespace Device
{

DisplayBacklight::DisplayBacklight(
		Driver::IAmbientLightSensorDriver &_ambientLightSensorDriver,
		Driver::IDisplayBacklightDriver &_displayBacklightDriver) :
		ambientLightSensorDriver(_ambientLightSensorDriver), displayBacklightDriver(
				_displayBacklightDriver)
{
}

void DisplayBacklight::init()
{
	ambientLightSensorDriver.init();
	displayBacklightDriver.init();
}

void DisplayBacklight::tick()
{
}

void DisplayBacklight::setBrightnessPercentage(uint8_t level)
{
	if(level > 100)
	{
		level = 100;
	}

	displayBacklightDriver.setBrightness(level);
}

uint16_t DisplayBacklight::getAmbientLightLevel()
{
	return ambientLightSensorDriver.getAmbientLightLevel();
}

}
