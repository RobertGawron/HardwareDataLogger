// BrightnessDriver.cpp
module;

#include <cstdint>

module Driver.BrightnessDriver;

namespace Driver
{
    auto BrightnessDriver::setBrightness(std::uint8_t brightness) noexcept -> bool
    {
        (void)brightness;

        return true;
    }
}