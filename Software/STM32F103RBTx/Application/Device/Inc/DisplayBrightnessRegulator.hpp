/**
 * @file DisplayBrightnessRegulator.hpp
 * @brief Declaration of the DisplayBrightnessRegulator class for managing display brightness.
 */

#ifndef DISPLAY_BRIGHTNESS_REGULATOR_HPP
#define DISPLAY_BRIGHTNESS_REGULATOR_HPP

#include "Device/Interface/IDisplayBrightnessRegulator.hpp"
#include "Driver/Interface/IAmbientLightSensorDriver.hpp"
#include "Driver/Interface/IDisplayBrightnessDriver.hpp"

#include <cstdint>

namespace Device
{
    /**
     * @class DisplayBrightnessRegulator
     * @brief Regulates the brightness of an LCD display based on ambient light and user preferences.
     */
    class DisplayBrightnessRegulator final : public IDisplayBrightnessRegulator
    {
    public:
        /**
         * @brief Constructs a DisplayBrightnessRegulator with specified sensor and display drivers.
         * @param ambientLightSensorDriver Reference to the ambient light sensor driver.
         * @param displayBrightnessDriver Reference to the display brightness driver.
         */
        explicit constexpr DisplayBrightnessRegulator(
            Driver::IAmbientLightSensorDriver &ambientLightSensorDriver,
            Driver::IDisplayBrightnessDriver &displayBrightnessDriver) noexcept
            : ambientLightSensorDriver{ambientLightSensorDriver}, displayBrightnessDriver{displayBrightnessDriver}
        {
        }

        ~DisplayBrightnessRegulator() override = default;

        // Non-copyable and non-movable
        DisplayBrightnessRegulator(const DisplayBrightnessRegulator &) = delete;
        DisplayBrightnessRegulator(DisplayBrightnessRegulator &&) = delete;
        DisplayBrightnessRegulator &operator=(const DisplayBrightnessRegulator &) = delete;
        DisplayBrightnessRegulator &operator=(DisplayBrightnessRegulator &&) = delete;

        /**
         * @brief Initializes the display brightness regulator.
         * @return true if initialization is successful, false otherwise.
         */
        [[nodiscard]] bool init() noexcept override;

        /**
         * @brief Updates the brightness regulator state.
         */
        void tick() noexcept override;

        /**
         * @brief Returns the current brightness level as a percentage.
         * @return Brightness level (0-100).
         */
        [[nodiscard]] std::uint8_t getBrightnessPercentage() const noexcept override;

        /**
         * @brief Sets the display brightness level.
         * @param level Brightness percentage (0-100).
         * @return true if the level is set successfully.
         */
        [[nodiscard]] bool setBrightnessPercentage(std::uint8_t level) noexcept override;

    private:
        Driver::IAmbientLightSensorDriver &ambientLightSensorDriver;
        Driver::IDisplayBrightnessDriver &displayBrightnessDriver;
        std::uint8_t level{0};
    };

} // namespace Device

#endif // DISPLAY_BRIGHTNESS_REGULATOR_HPP