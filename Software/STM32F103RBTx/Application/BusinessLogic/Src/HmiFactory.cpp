#include "BusinessLogic/Inc/HmiFactory.hpp"

// #include "Driver/Inc/St7735DisplayDriver.hpp"

#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/DisplayBrightnessRegulator.hpp"

#include "BusinessLogic/Inc/HmiDataModel.hpp"
#include "BusinessLogic/Inc/HmiViewManager.hpp"
#include "BusinessLogic/Inc/HmiInputController.hpp"

namespace BusinessLogic
{
    HmiFactory::HmiFactory(IPlatformFactory &_platformFactory)
        : platformFactory(_platformFactory)
    {
    }

    IHmiDataModel &HmiFactory::getDataModel()
    {
        static Device::DisplayBrightnessRegulator brightnessRegulator(
            platformFactory.createAmbientLightSensorDriver(),
            platformFactory.createDisplayBrightnessDriver());

        // static Device::DisplayBrightnessRegulator brightnessRegulator = getDisplayBrightnessRegulator();
        static HmiDataModel model(brightnessRegulator);
        return model;
    }

    IHmiInputController &HmiFactory::getInputController()
    {
        static Device::IKeyboard &keyboard = getKeyboard();
        static HmiInputController controller(keyboard);
        return controller;
    }

    IHmiViewManager &HmiFactory::getHmiViewManager()
    {
        static Driver::IDisplayDriver &display = getDisplay();
        static HmiViewManager view(display);
        return view;
    }

    Driver::IDisplayDriver &HmiFactory::getDisplay()
    {
        // TODO change name of createDisplayDriver, its called twice
        return platformFactory.createDisplayDriver();
    }

    Device::IDisplayBrightnessRegulator &HmiFactory::getDisplayBrightnessRegulator()
    {
        // not used
        static Device::DisplayBrightnessRegulator brightnessRegulator(
            platformFactory.createAmbientLightSensorDriver(),
            platformFactory.createDisplayBrightnessDriver());

        // tmp
        // brightnessRegulator.init();

        return brightnessRegulator;
    }
    Device::IKeyboard &HmiFactory::getKeyboard()
    {
        static Device::Keyboard keyboard(platformFactory.createKeyboardDriver());
        return keyboard;
    }

}