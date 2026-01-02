/**
 * @file DisplayBrightness.hpp
 * @brief Declaration of the DisplayBrightness class for managing display brightness.
 */

#ifndef DISPLAY_BRIGHTNESS_HPP
#define DISPLAY_BRIGHTNESS_HPP

#include "Device/Inc/DeviceComponent.hpp"
#include "LightSensorDriver.hpp"
#include "BrightnessDriver.hpp"

#include <cstdint>

namespace Device
{
    /**
     * @class DisplayBrightness
     * @brief Regulates the brightness of an LCD display based on ambient light and user preferences.
     */
    class DisplayBrightness final : public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a DisplayBrightness with specified sensor and display drivers.
         * @param LightSensorDriver Reference to the ambient light sensor driver.
         * @param displayBrightness Reference to the display brightness driver.
         */
        explicit constexpr DisplayBrightness(
            Driver::LightSensorDriver &lightSensorDriver,
            Driver::BrightnessDriver &displayBrightness) noexcept
            : lightSensorDriver{lightSensorDriver}, displayBrightness{displayBrightness}
        {
        }

        ~DisplayBrightness() = default;

        // Non-copyable and non-movable
        DisplayBrightness(const DisplayBrightness &) = delete;
        DisplayBrightness(DisplayBrightness &&) = delete;
        DisplayBrightness &operator=(const DisplayBrightness &) = delete;
        DisplayBrightness &operator=(DisplayBrightness &&) = delete;

        /**
         * @brief Initializes the display brightness regulator.
         * @return true if initialization is successful, false otherwise.
         */
        [[nodiscard]] bool onInit() noexcept;

        [[nodiscard]] bool onStart() noexcept;
        //  [[nodiscard]] bool onStop() noexcept;
        /**
         * @brief Returns the current brightness level as a percentage.
         * @return Brightness level (0-100).
         */
        [[nodiscard]] std::uint8_t getBrightnessPercentage() const noexcept;

        /**
         * @brief Sets the display brightness level.
         * @param level Brightness percentage (0-100).
         * @return true if the level is set successfully.
         */
        [[nodiscard]] bool setBrightnessPercentage(std::uint8_t level) noexcept;

    private:
        Driver::LightSensorDriver &lightSensorDriver;
        Driver::BrightnessDriver &displayBrightness;
        std::uint8_t level{0};
    };

} // namespace Device

#endif // DISPLAY_BRIGHTNESS_REGULATOR_HPP