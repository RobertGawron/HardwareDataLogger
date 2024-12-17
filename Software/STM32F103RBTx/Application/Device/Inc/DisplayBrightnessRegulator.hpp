/**
 * @file DisplayBrightnessRegulator.hpp
 * @brief Declaration of the DisplayBrightnessRegulator class for managing display brightness.
 *
 * This file contains the declaration of the DisplayBrightnessRegulator class, which adjusts the
 * backlight of an LCD display based on ambient light levels and user preferences.
 */

#ifndef DisplayBrightnessRegulator_H_
#define DisplayBrightnessRegulator_H_

#include "Device/Interfaces/IDisplayBrightnessRegulator.hpp"
#include "Driver/Interfaces/IAmbientLightSensorDriver.hpp"
#include "Driver/Interfaces/IDisplayBrightnessDriver.hpp"

namespace Device
{
    /**
     * @class DisplayBrightnessRegulator
     * @brief Regulates the brightness of an LCD display based on ambient light and user preferences.
     *
     * The DisplayBrightnessRegulator class is responsible for adjusting the backlight brightness of
     * an LCD display according to the ambient light detected by a sensor and user-defined settings.
     * It interacts with platform-specific drivers for the ambient light sensor and display backlight.
     */
    class DisplayBrightnessRegulator : public IDisplayBrightnessRegulator
    {
    public:
        /**
         * @brief Constructs a DisplayBrightnessRegulator object with the given sensor and display drivers.
         *
         * @param _ambientLightSensorDriver Reference to the ambient light sensor driver.
         * @param _displayBrightnessDriver Reference to the display brightness driver.
         */
        explicit DisplayBrightnessRegulator(
            Driver::IAmbientLightSensorDriver &_ambientLightSensorDriver,
            Driver::IDisplayBrightnessDriver &_displayBrightnessDriver);

        /**
         * @brief Default virtual destructor.
         */
        ~DisplayBrightnessRegulator() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        DisplayBrightnessRegulator(const DisplayBrightnessRegulator &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent copying.
         */
        DisplayBrightnessRegulator &operator=(const DisplayBrightnessRegulator &) = delete;

        /**
         * @brief Initializes the display brightness regulator.
         *
         * Sets up necessary configurations for the ambient light sensor and display brightness drivers.
         *
         * @return true if initialization is successful, false otherwise.
         */
        bool init() override;

        /**
         * @brief Ticks the brightness regulator state machine.
         *
         * This method should be called periodically to update the brightness level based on ambient light changes
         * and user preferences.
         */
        void tick() override;

        /**
         * @brief Gets the current brightness level as a percentage.
         *
         * This method is primarily for debugging purposes and returns the current brightness level of the display
         * as a percentage.
         *
         * @return The brightness level as a percentage (0-100).
         */
        [[nodiscard]] std::uint8_t getBrightnessPercentage() const override;

        /**
         * @brief Sets the brightness level as a percentage.
         *
         * This method is primarily for debugging purposes and sets the brightness level of the display
         * to a specific percentage.
         *
         * @param level The brightness level to set, in percentage (0-100).
         */
        void setBrightnessPercentage(std::uint8_t level) override;

    private:
        /** @brief Reference to the platform-specific ambient light sensor driver. */
        Driver::IAmbientLightSensorDriver &ambientLightSensorDriver;

        /** @brief Reference to the platform-specific display brightness driver. */
        Driver::IDisplayBrightnessDriver &displayBrightnessDriver;

        /** @brief Current brightness level (0-100), used for temporary debugging. */
        std::uint8_t level = 0u;
    };
}

#endif // DisplayBrightnessRegulator_H_
