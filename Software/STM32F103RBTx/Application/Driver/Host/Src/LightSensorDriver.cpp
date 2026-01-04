#include "LightSensorDriver.hpp"

#include <cstdint>

namespace Driver
{

    std::uint32_t LightSensorDriver::getAmbientLightLevel() const noexcept
    {
        // arbitrary value
        const std::uint32_t adcResult = 10U;

        return adcResult;
    }

}
