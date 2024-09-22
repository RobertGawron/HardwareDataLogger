#include "HmiFactory.hpp"

#include "St7735DisplayDriver.hpp"

#include "Keyboard.hpp"
#include "DisplayBrightnessRegulator.hpp"

#include "HmiDataModel.hpp"
#include "HmiViewManager.hpp"
#include "HmiInputController.hpp"

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
        static Driver::St7735DisplayDriver display;

        return display;
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