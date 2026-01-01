#include "Device/Inc/DisplayBrightnessRegulator.hpp"

#include <cstddef>
#include <cstdint>

namespace Device
{
    bool DisplayBrightnessRegulator::init() noexcept
    {
        ambientLightSensorDriver.initialize();
        displayBrightnessDriver.initialize();

        ambientLightSensorDriver.start();
        displayBrightnessDriver.start();

        // TODO: Remove dummy brightness test sweep
        static constexpr std::uint8_t START_BRIGHTNESS{1};
        static constexpr std::uint8_t STOP_BRIGHTNESS{95};
        static constexpr std::uint8_t BRIGHTNESS_STEP{10};

        for (std::uint8_t i{START_BRIGHTNESS}; i < STOP_BRIGHTNESS; i += BRIGHTNESS_STEP)
        {
            const auto brightness = static_cast<Driver::IDisplayBrightnessDriver::BrightnessPercentage>(i);
            displayBrightnessDriver.setBrightness(brightness);
        }

        return true;
    }

    void DisplayBrightnessRegulator::tick() noexcept
    {
        [[maybe_unused]] const auto ambientLevel = ambientLightSensorDriver.getAmbientLightLevel();
        // TODO: Implement automatic brightness adjustment based on ambient light
    }

    std::uint8_t DisplayBrightnessRegulator::getBrightnessPercentage() const noexcept
    {
        return level;
    }

    bool DisplayBrightnessRegulator::setBrightnessPercentage(std::uint8_t newLevel) noexcept
    {
        static constexpr std::uint8_t MAX_BRIGHTNESS_LEVEL{100};

        if (newLevel >= MAX_BRIGHTNESS_LEVEL) [[unlikely]]
        {
            return false;
        }

        level = newLevel;
        displayBrightnessDriver.setBrightness(level);

        return true;
    }

} // namespace Device