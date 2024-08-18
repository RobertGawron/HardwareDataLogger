#include "ApplicationBuilder.hpp"
#include "ST7735DisplayDriver.hpp"
#include "ST7735DisplayBacklightDriver.hpp"
#include "KeyboardFourPushButtonsDriver.hpp"
#include "AmbientLightSensorDriver.hpp"

namespace BusinessLogic
{

    ApplicationBuilder::ApplicationBuilder() : ambientLightSensorDriver(new Driver::AmbientLightSensorDriver()),
                                               displayBacklightDriver(new Driver::ST7735DisplayBacklightDriver()),
                                               displayBacklight(*ambientLightSensorDriver, *displayBacklightDriver),
                                               keyboardDriver(new Driver::KeyboardFourPushButtonsDriver()),
                                               keyboard(*keyboardDriver),
                                               display(new Driver::ST7735DisplayDriver()),
                                               hmi(displayBacklight, keyboard, *display)
    {
    }

    ApplicationBuilder::~ApplicationBuilder()
    {
        if (ambientLightSensorDriver != nullptr)
        {
            delete ambientLightSensorDriver;
            ambientLightSensorDriver = nullptr;
        }

        if (displayBacklightDriver != nullptr)
        {
            delete displayBacklightDriver;
            displayBacklightDriver = nullptr;
        }

        if (keyboardDriver != nullptr)
        {
            delete keyboardDriver;
            keyboardDriver = nullptr;
        }

        if (display != nullptr)
        {
            delete display;
            display = nullptr;
        }
    }

    void ApplicationBuilder::init()
    {
        displayBacklight.init();
        display->init();

        keyboard.init();
        hmi.init();
    }

    void ApplicationBuilder::tick()
    {
        displayBacklight.tick();

        keyboard.tick();
        hmi.tick();
    }

}
