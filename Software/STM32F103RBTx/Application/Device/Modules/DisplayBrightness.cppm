/**
 * @file DisplayBrightness.cppm
 * @brief Declaration of the DisplayBrightness class for managing display brightness.
 */
module;

#include <cstdint>

export module Device.DisplayBrightness;

import Device.DeviceComponent;

import Driver.DriverComponent;
import Driver.LightSensorDriver;
import Driver.BrightnessDriver;

export namespace Device
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
        [[nodiscard]] auto onInit() noexcept -> bool;

        [[nodiscard]] auto onStart() noexcept -> bool;
        //  [[nodiscard]] bool onStop() noexcept;
        /**
         * @brief Returns the current brightness level as a percentage.
         * @return Brightness level (0-100).
         */
        [[nodiscard]] auto getBrightnessPercentage() const noexcept -> std::uint8_t;

        /**
         * @brief Sets the display brightness level.
         * @param level Brightness percentage (0-100).
         * @return true if the level is set successfully.
         */
        [[nodiscard]] auto setBrightnessPercentage(std::uint8_t level) noexcept -> bool;

    private:
        Driver::LightSensorDriver &lightSensorDriver;
        Driver::BrightnessDriver &displayBrightness;
        std::uint8_t level{0};
    };

} // namespace Device