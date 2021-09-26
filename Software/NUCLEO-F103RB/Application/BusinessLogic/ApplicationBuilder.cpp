#include <ApplicationBuilder.h>
#include <ST7735DisplayDriver.h>
#include "ST7735DisplayBacklightDriver.h"
#include "DummyAmbientLightSensorDriver.h"

namespace Application
{

ApplicationBuilder::ApplicationBuilder() :
		ambientLightSensorDriver(new Driver::DummyAmbientLightSensorDriver()),
		displayBacklightDriver(new Driver::ST7735DisplayBacklightDriver()),
		displayBacklight(*ambientLightSensorDriver, *displayBacklightDriver),
		keyboard(),
		display(new Driver::ST7735DisplayDriver()),
		hmi(displayBacklight, keyboard, *display)
{
}

ApplicationBuilder::~ApplicationBuilder()
{
}


void ApplicationBuilder::init()
{
	hmi.init();
}

void ApplicationBuilder::tick()
{
	hmi.tick();
}

}


