module;

#include <cstddef>
#include <cstdint>

module Device.DisplayBrightness;

namespace Device
{
    auto DisplayBrightness::onInit() noexcept -> bool
    {
        const bool status = /*lightSensorDriver.init() && */ displayBrightness.init();

        return status;
    }

    auto DisplayBrightness::onStart() noexcept -> bool
    {
        bool status = lightSensorDriver.start() && displayBrightness.start();

        // TODO: Remove dummy brightness test sweep
        static constexpr std::uint8_t START_BRIGHTNESS{1};
        static constexpr std::uint8_t STOP_BRIGHTNESS{95};
        static constexpr std::uint8_t BRIGHTNESS_STEP{10};

        for (std::uint8_t i{START_BRIGHTNESS}; i < STOP_BRIGHTNESS; i += BRIGHTNESS_STEP)
        {
            const auto brightness = i;
            status &= displayBrightness.setBrightness(brightness);
        }

        return status;
    }

    auto DisplayBrightness::getBrightnessPercentage() const noexcept -> std::uint8_t
    {
        return level;
    }

    auto DisplayBrightness::setBrightnessPercentage(std::uint8_t newLevel) noexcept -> bool
    {
        static constexpr std::uint8_t MAX_BRIGHTNESS_LEVEL{100};

        bool status = (newLevel < MAX_BRIGHTNESS_LEVEL);
        if (status)
        {
            status = displayBrightness.setBrightness(level);

            if (status)
            {
                level = newLevel;
            }
        }

        return status;
    }

} // namespace Device