#ifndef DISPLAYCONFIGURATOR_H_
#define DISPLAYCONFIGURATOR_H_

#include "DisplayBacklight.h"

namespace Application
{

class DisplayConfigurator
{
public:
	DisplayConfigurator();
	virtual ~DisplayConfigurator();
	void tick();
private:
	Device::DisplayBacklight mDisplayBacklight;
};

}

#endif
