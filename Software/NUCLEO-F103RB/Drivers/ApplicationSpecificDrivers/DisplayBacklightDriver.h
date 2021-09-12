#ifndef DISPLAYBACKLIGHTDRIVER_H_
#define DISPLAYBACKLIGHTDRIVER_H_

namespace Driver
{

class DisplayBacklightDriver
{
public:
	DisplayBacklightDriver();
	virtual ~DisplayBacklightDriver();
	void init();
	void setBrightness(int value);
	int getBrightness();
private:
	int brightness;
};

}

#endif
