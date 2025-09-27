/**
 * @file DisplayBrightnessRegulator.hpp
 * @brief Declaration of the DisplayBrightnessRegulator class for managing display brightness.
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
     */
    class DisplayBrightnessRegulator : public IDisplayBrightnessRegulator
    {
    public:
        /**
         * @brief Constructs a DisplayBrightnessRegulator with specified sensor and display drivers.
         * @param _ambientLightSensorDriver Reference to the ambient light sensor driver.
         * @param _displayBrightnessDriver Reference to the display brightness driver.
         */
        explicit DisplayBrightnessRegulator(
            Driver::IAmbientLightSensorDriver &_ambientLightSensorDriver,
            Driver::IDisplayBrightnessDriver &_displayBrightnessDriver);

        ~DisplayBrightnessRegulator() override = default; ///< Default virtual destructor.

        DisplayBrightnessRegulator(const DisplayBrightnessRegulator &) = delete; ///< Deleted copy constructor.
        DisplayBrightnessRegulator &operator=(const DisplayBrightnessRegulator &) = delete; ///< Deleted copy assignment.

        /**
         * @brief Initializes the display brightness regulator.
         * @return true if initialization is successful, false otherwise.
         */
        bool init() override;

        /**
         * @brief Updates the brightness regulator state.
         */
        void tick() override;

        /**
         * @brief Returns the current brightness level as a percentage.
         * @return Brightness level (0-100).
         */
        [[nodiscard]] std::uint8_t getBrightnessPercentage() const override;

        /**
         * @brief Sets the display brightness level.
         * @param level Brightness percentage (0-100).
         * @return true if the level is set successfully.
         */
        bool setBrightnessPercentage(std::uint8_t level) override;

    private:
        Driver::IAmbientLightSensorDriver &ambientLightSensorDriver; ///< Ambient light sensor driver.
        Driver::IDisplayBrightnessDriver &displayBrightnessDriver;   ///< Display brightness driver.
        std::uint8_t level = 0u; ///< Current brightness level (0-100).
    };
}

#endif // DisplayBrightnessRegulator_H_
