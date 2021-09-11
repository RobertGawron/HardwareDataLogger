#ifndef APPLICATIONSPECIFICDRIVERS_DISPLAYDRIVER_H_
#define APPLICATIONSPECIFICDRIVERS_DISPLAYDRIVER_H_

namespace Driver
{

class DisplayDriver
{
public:
	DisplayDriver();
	virtual ~DisplayDriver();

	void update();
};

}

#endif
