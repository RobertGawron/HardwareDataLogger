#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_

#include "IDisplay.h"

namespace Driver
{

class ST7735DisplayDriver : public Device::IDisplay
{
public:
	ST7735DisplayDriver() = default;
	virtual ~ST7735DisplayDriver() = default;

	void init();
	virtual void showBacklightConf_ForDebugOnly(uint16_t ambientLight, uint8_t brightnessPercentage);
};

}

#endif
