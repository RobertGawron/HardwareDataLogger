#ifndef HMI_H_
#define HMI_H_

#include "DisplayBacklight.h"
#include "Keyboard.h"
#include "IDisplay.h"

namespace Application
{

class HMI
{
public:
    HMI(Device::DisplayBacklight &_displayBacklight,
        Device::Keyboard &_keyboard,
        Device::IDisplay &_display);
    virtual ~HMI() = default;

    void init();
    void tick();

private:
    Device::DisplayBacklight &displayBacklight;
    Device::Keyboard &keyboard;
    Device::IDisplay &display;

    static const uint8_t displayBrightnessDefault = 50U;
    uint8_t displayBrightnessActual;

    // this is temporary
    ::Driver::KeboardKeyState prevUp;
    ::Driver::KeboardKeyState prevDown;
};

}

#endif
