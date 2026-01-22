module;

#include "mui.h"
#include "u8g2.h"
#include "mui_u8g2.h"

module BusinessLogic.HmiFacade;

import Device;
import Driver;

namespace BusinessLogic
{
    HmiFacade::HmiFacade(
        Device::Display &_display,
        Device::DisplayBrightness &_displayBrightness,
        Device::Keyboard &_keyboard) : display(_display),
                                       displayBrightness(_displayBrightness),
                                       keyboard(_keyboard)
    {
    }

    auto HmiFacade::onInit() noexcept -> bool
    {
        /* const bool status = keyboard.init() &&
                             displayBrightness.init() &&
                             display.init();*/

        const bool status = true;

        // inherit , need init anyway
        displayBrightness.init();
        display.init();

        return status;
    }

    auto HmiFacade::onStart() noexcept -> bool
    {
        const bool status = true;

        /*const bool status = keyboard.start() &&
                            displayBrightness.start() &&
                            display.init();
*/
        displayBrightness.start();
        display.start();

        //  displayBrightness.setBrightnessPercentage(50);
        return status;
    }

    auto HmiFacade::onStop() noexcept -> bool
    {
        const bool status = keyboard.stop() &&
                            displayBrightness.stop() &&
                            display.stop();
        return status;
    }

    auto HmiFacade::onTick() noexcept -> bool
    {
        bool status = keyboard.tick();

        return status;
    }

}