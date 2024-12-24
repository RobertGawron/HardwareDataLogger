/**
 * @file BrightnessDriverStub.hpp
 * @brief Defines the BrightnessDriverStub class for controlling the backlight brightness
 *        of an LCD via PWM.
 */

#ifndef BrightnessDriverStub_H_
#define BrightnessDriverStub_H_

#include "Driver/Interfaces/IDisplayBrightnessDriver.hpp"

#include <stdint.h>

namespace Driver
{
    /**
     * @class BrightnessDriverStub
     * @brief Handles the backlight level of the LCD using Pulse Width Modulation (PWM).
     *
     * This class provides methods to initialize and control the brightness of an LCD backlight.
     * It interfaces with the hardware using PWM signals to adjust the brightness level.
     *
     * The PWM frequency is set to 5 kHz.
     */
    class BrightnessDriverStub : public IDisplayBrightnessDriver
    {
    public:
        /**
         * @brief Default constructor for BrightnessDriverStub.
         *
         */
        BrightnessDriverStub() = default;

        /**
         * @brief Default destructor for BrightnessDriverStub.
         */
        virtual ~BrightnessDriverStub() = default;

        // Delete copy constructor and assignment operator

        /**
         * @brief Copy constructor for BrightnessDriverStub.
         *
         * Deleted to prevent copying of the driver instance.
         */
        BrightnessDriverStub(const BrightnessDriverStub &) = delete;

        /**
         * @brief Copy assignment operator for BrightnessDriverStub.
         *
         * Deleted to prevent assignment of the driver instance.
         */
        BrightnessDriverStub &operator=(const BrightnessDriverStub &) = delete;

        /**
         * @brief Initializes the display brightness driver.
         *
         * Configures the underlying timer and PWM settings.
         *
         * @return True if initialization is successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the PWM for controlling the display brightness.
         *
         * This method starts the PWM signal generation with an initial brightness setting.
         *
         * @return True if the PWM starts successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the PWM and turns off the display backlight.
         *
         * @return True if the PWM stops successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the display brightness driver to its default state.
         *
         * @return True if the reset is successful, false otherwise.
         */
        bool onReset() override;

        /**
         * @brief Sets the brightness of the display.
         *
         * Adjusts the PWM duty cycle to set the desired brightness level.
         *
         * @param brightness Brightness level as a percentage (0-100).
         * @return True if the brightness is set successfully, false otherwise.
         */
        virtual bool setBrightness(BrightnessPercentage brightness) override;
    };

}

#endif // BrightnessDriverStub_H_
