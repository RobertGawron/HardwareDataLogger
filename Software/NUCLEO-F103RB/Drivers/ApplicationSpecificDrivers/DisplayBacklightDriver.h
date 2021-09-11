#ifndef DISPLAYBACKLIGHTDRIVER_H_
#define DISPLAYBACKLIGHTDRIVER_H_

namespace Driver
{

class DisplayBacklightDriver
{
public:
	DisplayBacklightDriver();
	virtual ~DisplayBacklightDriver();
	void tick();
};

}

#endif
