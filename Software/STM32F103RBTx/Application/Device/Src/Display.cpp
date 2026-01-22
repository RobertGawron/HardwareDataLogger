module;

#include <array>
#include <cstdint>
#include <cstdlib>

#include "u8g2.h"
#include "u8x8.h"

module Device.Display;

// import Driver.DisplayPixelColor;
// import Device.DisplayPixelColor;

namespace Device
{
    /* Display::Display(Driver::DisplayDriver &_displayDriver) : displayDriver(_displayDriver)
     {
     }*/

    bool Display::onInit() noexcept
    {
        return displayDriver.init();
        ;
    }

    bool Display::onStart() noexcept
    {

        return displayDriver.start();
    }
    bool Display::onStop() noexcept
    {

        return true;
    }

} // namespace Device