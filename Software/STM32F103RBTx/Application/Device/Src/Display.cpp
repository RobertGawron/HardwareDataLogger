module;

#include <cstdint>

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