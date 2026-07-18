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

    auto LightSensorDriver::startAdc() noexcept -> bool
    {
        return true;
    }

    auto LightSensorDriver::stopAdc() noexcept -> bool
    {
        return true;
    }
}