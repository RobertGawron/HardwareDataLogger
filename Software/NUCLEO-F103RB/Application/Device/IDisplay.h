#ifndef IDISPLAY_H_
#define IDISPLAY_H_

#include <stdint.h>

namespace Device
{

class IDisplay {
    public:
	virtual ~IDisplay() = default;

	virtual void init() = 0;
	virtual void showBacklightConf_ForDebugOnly(uint16_t ambientLight, uint8_t brightnessPercentage) = 0;
    //virtual void setPixel() = 0;
};

}

#endif
