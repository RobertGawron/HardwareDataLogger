#include "Device/Inc/DisplayBrightnessRegulator.hpp"
#include "Driver/Interfaces/IDisplayBrightnessDriver.hpp"
#include "Driver/Interfaces/IAmbientLightSensorDriver.hpp"

#include <cstdint>
#include <cstddef>

namespace Device
{

    DisplayBrightnessRegulator::DisplayBrightnessRegulator(
        Driver::IAmbientLightSensorDriver &_ambientLightSensorDriver,
        Driver::IDisplayBrightnessDriver &_displayBrightnessDriver) : ambientLightSensorDriver(_ambientLightSensorDriver), displayBrightnessDriver(_displayBrightnessDriver)
    {
    }

    bool DisplayBrightnessRegulator::init()
    {
        bool status = false;

        ambientLightSensorDriver.initialize();
        displayBrightnessDriver.initialize();

        ambientLightSensorDriver.start();
        displayBrightnessDriver.start();

        // dummy test
        std::uint8_t start = 1;
        std::uint8_t stop = 95;
        std::uint8_t step = 10;

        for (std::size_t i = start; i < stop; i += step)
        {
            displayBrightnessDriver.setBrightness(i);
            status = true; // dummy
        }
        // displayBrightnessDriver.setBrightness(55);
        // displayBrightnessDriver.setBrightness(90);

        return status;
    }

    void DisplayBrightnessRegulator::tick()
    {
        volatile std::uint32_t dummy = ambientLightSensorDriver.getAmbientLightLevel();
        (void)dummy; // Suppress unused warning by explicitly marking it as used
    }

    std::uint8_t DisplayBrightnessRegulator::getBrightnessPercentage() const
    {
        return level;
    }

    bool DisplayBrightnessRegulator::setBrightnessPercentage(std::uint8_t _level)
    {
        const std::uint8_t MaxLevel = 100u;
        bool status = false;

        if (_level < MaxLevel)
        {
            level = _level;
            status = true;

            displayBrightnessDriver.setBrightness(level);
        }

        return status;
    }

}
