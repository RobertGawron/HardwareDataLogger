// BrightnessDriver.cpp
module;

#include <cstdint>

module Driver.BrightnessDriver;

namespace Driver
{
    bool BrightnessDriver::setBrightness(std::uint8_t brightness) noexcept
    {
        (void)brightness;

        return true;
    }
}