#include "DisplayConfigurator.h"

namespace Application
{

DisplayConfigurator::DisplayConfigurator() :
		mDisplayBacklight()
{
}

DisplayConfigurator::~DisplayConfigurator()
{
}

void DisplayConfigurator::tick()
{
	mDisplayBacklight.tick();
}

}
