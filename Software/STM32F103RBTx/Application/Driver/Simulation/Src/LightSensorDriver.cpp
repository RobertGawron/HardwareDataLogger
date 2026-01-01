module;

#include <cstdint>
#include <span>

module Driver.LightSensorDriver;

namespace Driver
{
    auto LightSensorDriver::samples() const noexcept
        -> std::span<const std::uint16_t>
    {
        return std::span{adcDmaBuffer};
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