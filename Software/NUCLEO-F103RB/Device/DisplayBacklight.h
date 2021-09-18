#ifndef DISPLAYBACKLIGHT_H_
#define DISPLAYBACKLIGHT_H_

#include "IAmbientLightSensorDriver.h"
#include "IDisplayBacklightDriver.h"

namespace Device
{

class DisplayBacklight
{
public:
	DisplayBacklight(
			Driver::IAmbientLightSensorDriver& _ambientLightSensorDriver,
			Driver::IDisplayBacklightDriver& _displayBacklightDriver);
	virtual ~DisplayBacklight() = default;

	void init();
	void tick();

	uint16_t getAmbientLightLevel();
	void setBrightnessPercentage(uint8_t level);

private:
	Driver::IAmbientLightSensorDriver& ambientLightSensorDriver;
	Driver::IDisplayBacklightDriver& displayBacklightDriver;
};

}

#endif
