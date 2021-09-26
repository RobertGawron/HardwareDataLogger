#ifndef APPLICATIONBUILDER_H_
#define APPLICATIONBUILDER_H_

#include "ST7735DisplayDriver.h"
#include "IAmbientLightSensorDriver.h"
#include "IDisplayBacklightDriver.h"
#include "DisplayBacklight.h"
#include "Keyboard.h"
#include "IDisplay.h"
#include "HMI.h"

namespace Application
{

class ApplicationBuilder
{
public:
    ApplicationBuilder();
    ~ApplicationBuilder();

    void init();
    void tick();

private:
    Driver::IAmbientLightSensorDriver* ambientLightSensorDriver;
    Driver::IDisplayBacklightDriver* displayBacklightDriver;
    Device::DisplayBacklight displayBacklight;
    Device::Keyboard keyboard;
    Device::IDisplay *display;
    Application::HMI hmi;
};

}

#endif
