#ifndef APPLICATIONSPECIFICDRIVERS_DISPLAYDRIVER_H_
#define APPLICATIONSPECIFICDRIVERS_DISPLAYDRIVER_H_

namespace Driver
{

class DisplayDriver
{
public:
	DisplayDriver();
	virtual ~DisplayDriver();

	void init();

	// for debug
	void tmp_displayBacklightConf(int adc_value, int pwm_value, int brightness);
};

}

#endif
