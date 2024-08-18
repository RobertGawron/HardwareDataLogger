#include "DisplayBacklight.hpp"

namespace Device
{

    DisplayBacklight::DisplayBacklight(
        Driver::IAmbientLightSensorDriver &_ambientLightSensorDriver,
        Driver::IDisplayBacklightDriver &_displayBacklightDriver) : ambientLightSensorDriver(_ambientLightSensorDriver), displayBacklightDriver(_displayBacklightDriver)
    {
    }

    void DisplayBacklight::init()
    {
        ambientLightSensorDriver.init();
        displayBacklightDriver.init();
    }

    void DisplayBacklight::tick()
    {
    }

    uint8_t DisplayBacklight::getBrightnessPercentage()
    {
        return level;
    }

    void DisplayBacklight::setBrightnessPercentage(uint8_t _level)
    {
        level = _level;

        if (level > 100)
        {
            level = 100;
        }

        displayBacklightDriver.setBrightness(level);
    }

}
