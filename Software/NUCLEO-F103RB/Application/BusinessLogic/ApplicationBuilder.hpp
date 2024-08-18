#ifndef APPLICATIONBUILDER_H_
#define APPLICATIONBUILDER_H_

#ifdef __cplusplus
extern "C"
{
#include "ST7735DisplayDriver.hpp"
#include "IAmbientLightSensorDriver.hpp"
#include "IDisplayBacklightDriver.hpp"
#include "IKeyboardDriver.hpp"
#include "DisplayBacklight.hpp"
#include "Keyboard.hpp"
#include "IDisplay.hpp"
#include "HMI.hpp"

    void app_init();

    void app_tick();

    namespace BusinessLogic
    {
        class ApplicationBuilder
        {
        public:
            ApplicationBuilder();
            virtual ~ApplicationBuilder();

            void init();
            void tick();

        private:
            Driver::IAmbientLightSensorDriver *ambientLightSensorDriver = nullptr;
            Driver::IDisplayBacklightDriver *displayBacklightDriver = nullptr;
            Device::DisplayBacklight displayBacklight;

            Driver::IKeyboardDriver *keyboardDriver = nullptr;
            Device::Keyboard keyboard;

            Device::IDisplay *display = nullptr;
            BusinessLogic::HMI hmi;
        };
    }

    BusinessLogic::ApplicationBuilder builder;

    void app_init()
    {
        builder.init();
        // display.init()
    }
    void app_tick()
    {
        builder.tick();
    }
}
#endif

#endif
