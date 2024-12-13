#include "BusinessLogic/Inc/HmiFactory.hpp"

// #include "Driver/Inc/St7735DisplayDriver.hpp"

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
    /*
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
        }*/
#if 0 
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
#endif
}