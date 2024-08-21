#ifndef DisplayBrightnessRegulator_H_
#define DisplayBrightnessRegulator_H_

/**
 * @file DisplayBrightnessRegulator.h
 * @brief Declaration of the DisplayBrightnessRegulator class for managing display brightness.
 *
 * This file contains the declaration of the DisplayBrightnessRegulator class, which adjusts the
 * backlight of an LCD display based on ambient light levels and user preferences.
 */
#include "IDisplayBrightnessRegulator.hpp"
#include "IAmbientLightSensorDriver.hpp"
#include "IDisplayBrightnessDriver.hpp"

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
        virtual ~DisplayBrightnessRegulator() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        DisplayBrightnessRegulator(const DisplayBrightnessRegulator &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent copying.
         */
        DisplayBrightnessRegulator &operator=(const DisplayBrightnessRegulator &) = delete;
        virtual bool init();
        /**
         * @brief Initializes the display brightness regulator.
         *
         * Sets up necessary configurations for the ambient light sensor and display brightness drivers.
         *
         * @return true if initialization is successful, false otherwise.
         */

        /**
         * @brief Ticks the brightness regulator state machine.
         *
         * This method should be called periodically to update the brightness level based on ambient light changes
         * and user preferences.
         */
        void tick();

        /**
         * @brief Gets the current brightness level as a percentage.
         *
         * This method is primarily for debugging purposes and returns the current brightness level of the display
         * as a percentage.
         *
         * @return The brightness level as a percentage (0-100).
         */
        uint8_t getBrightnessPercentage() const;

        /**
         * @brief Sets the brightness level as a percentage.
         *
         * This method is primarily for debugging purposes and sets the brightness level of the display
         * to a specific percentage.
         *
         * @param level The brightness level to set, in percentage (0-100).
         */
        void setBrightnessPercentage(uint8_t level);

    private:
        Driver::IAmbientLightSensorDriver &ambientLightSensorDriver; /**< Reference to the platform-specific ambient light sensor driver. */
        Driver::IDisplayBrightnessDriver &displayBrightnessDriver;   /**< Reference to the platform-specific display brightness driver. */

        uint8_t level = 0u; /**< Current brightness level (0-100), used for temporary debugging. */
    };

}

#endif
