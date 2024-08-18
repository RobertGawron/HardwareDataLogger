#include "ApplicationBuilder.hpp"
#include "ST7735DisplayDriver.hpp"
#include "ST7735DisplayBacklightDriver.hpp"
#include "KeyboardKeysDriver.hpp"
#include "DummyAmbientLightSensorDriver.hpp"

namespace BusinessLogic
{

    ApplicationBuilder::ApplicationBuilder() : ambientLightSensorDriver(new Driver::DummyAmbientLightSensorDriver()),
                                               displayBacklightDriver(new Driver::ST7735DisplayBacklightDriver()),
                                               displayBacklight(*ambientLightSensorDriver, *displayBacklightDriver),
                                               keyboardKeysDriver(new Driver::KeyboardKeysDriver()),
                                               keyboard(*keyboardKeysDriver),
                                               display(new Driver::ST7735DisplayDriver()),
                                               hmi(displayBacklight, keyboard, *display)
    {
    }

    ApplicationBuilder::~ApplicationBuilder()
    {
        // todo add delete
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
