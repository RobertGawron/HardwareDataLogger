#ifndef IDISPLAYBACKLIGHTDRIVER_H_
#define IDISPLAYBACKLIGHTDRIVER_H_

#include <stdint.h>

namespace Driver
{

class IDisplayBacklightDriver
{
public:
	virtual ~IDisplayBacklightDriver() = default;

	virtual void init() = 0;
	virtual void setBrightness(uint16_t value) = 0;
	virtual uint16_t getBrightness() = 0;
};

}

#endif
