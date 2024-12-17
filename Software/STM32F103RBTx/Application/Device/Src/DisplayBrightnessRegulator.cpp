#include "Device/Inc/DisplayBrightnessRegulator.hpp"
#include "Driver/Interfaces/IDisplayBrightnessDriver.hpp"
#include "Driver/Interfaces/IAmbientLightSensorDriver.hpp"

#include <cstdint>

namespace Device
{

    DisplayBrightnessRegulator::DisplayBrightnessRegulator(
        Driver::IAmbientLightSensorDriver &_ambientLightSensorDriver,
        Driver::IDisplayBrightnessDriver &_displayBrightnessDriver) : ambientLightSensorDriver(_ambientLightSensorDriver), displayBrightnessDriver(_displayBrightnessDriver)
    {
    }

    bool DisplayBrightnessRegulator::init()
    {
        const bool status = false;

        ambientLightSensorDriver.initialize();
        displayBrightnessDriver.initialize();

        ambientLightSensorDriver.start();
        displayBrightnessDriver.start();
        /* if ()
         {
             status = true;
         }*/

        // dummy test
        for (int i = 1; i < 95; i += 10)
        {
            displayBrightnessDriver.setBrightness(i);
        }
        // displayBrightnessDriver.setBrightness(55);
        // displayBrightnessDriver.setBrightness(90);

        return true;
        // return status;
    }

    void DisplayBrightnessRegulator::tick()
    {
        volatile int dummy = ambientLightSensorDriver.getAmbientLightLevel();
    }

    std::uint8_t DisplayBrightnessRegulator::getBrightnessPercentage() const
    {
        return level;
    }

    void DisplayBrightnessRegulator::setBrightnessPercentage(std::uint8_t _level)
    {
        // todo ake it bool
        level = _level;

        if (level > 100)
        {
            level = 100;
        }

        displayBrightnessDriver.setBrightness(level);
    }

}
