module;

#include <cstddef>
#include <cstdint>

module Device.DisplayBrightness;

namespace Device
{

    auto DisplayBrightness::onInit() noexcept -> bool
    {
        const bool status = lightSensor.init() &&
                            displayBrightness.init();

        return status;
    }

    auto DisplayBrightness::onStart() noexcept -> bool
    {
        const bool status = lightSensor.start() &&
                            displayBrightness.start();

        return status;
    }

    auto DisplayBrightness::onStop() noexcept -> bool
    {
        const bool status = lightSensor.stop() &&
                            displayBrightness.stop();

        return status;
    }

    auto DisplayBrightness::getBrightnessPercentage()
        const noexcept -> std::uint8_t
    {
        return brightness;
    }

    auto DisplayBrightness::setBrightnessPercentage(
        std::uint8_t percentage) noexcept -> bool
    {
        // check in the driver if brightness level is correct
        const bool status = displayBrightness.setBrightness(percentage);

        if (status)
        {
            brightness = percentage;
        }

        return status;
    }

} // namespace Device