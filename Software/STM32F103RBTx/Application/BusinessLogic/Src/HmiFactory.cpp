#include "BusinessLogic/Inc/HmiFactory.hpp"

#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"

#include "BusinessLogic/Inc/HmiMui.hpp"

#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/DisplayBrightnessRegulator.hpp"

namespace BusinessLogic
{
    HmiFactory::HmiFactory(IPlatformFactory &platformFactory)
        : display(platformFactory.createDisplayDriver()),
          brightnessRegulator(
              platformFactory.createAmbientLightSensorDriver(),
              platformFactory.createDisplayBrightnessDriver()),
          keyboard(platformFactory.createKeyboardDriver()),
          hmi(display,
              brightnessRegulator,
              keyboard)
    {
    }

    bool HmiFactory::initialize()
    {
        return hmi.initialize();
    }

    bool HmiFactory::start()
    {
        return hmi.start();
    }

    bool HmiFactory::tick()
    {
        return hmi.tick();
    }

}
