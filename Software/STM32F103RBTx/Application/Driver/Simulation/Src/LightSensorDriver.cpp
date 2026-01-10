// LightSensorDriver.cpp
module;

#include <cstdint>

module Driver.LightSensorDriver;

namespace Driver
{
    std::uint32_t LightSensorDriver::getAmbientLightLevel() const noexcept
    {
        // arbitrary value
        const std::uint32_t adcResult = 10U;

        return adcResult;
    }

    bool LightSensorDriver::startAdc() noexcept
    {
        return true;
    }

    bool LightSensorDriver::stopAdc() noexcept
    {
        return true;
    }
}