#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
#include "BusinessLogic/Inc/HmiFactory.hpp"
#include "BusinessLogic/Inc/HmiMui.hpp"
#include "Device/Interfaces/IMeasurementReader.hpp"
#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/DisplayBrightnessRegulator.hpp"

namespace BusinessLogic
{
    HmiFactory::HmiFactory(Device::IMeasurementReader &reader,
                           IPlatformFactory &platformFactory) : hmiMeasurementModel(reader),
                                                                display(platformFactory.createDisplayDriver()),
                                                                brightnessRegulator(
                                                                    platformFactory.createAmbientLightSensorDriver(),
                                                                    platformFactory.createDisplayBrightnessDriver()),
                                                                keyboard(platformFactory.createKeyboardDriver()),
                                                                hmi(hmiMeasurementModel,
                                                                    display,
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

    // todo shoudnt have tick method
    bool HmiFactory::tick()
    {
        return hmi.tick();
    }
}
