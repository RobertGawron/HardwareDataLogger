/**
 * @file St7735DisplayBrightnessDriver.hpp
 * @brief Defines the St7735DisplayBrightnessDriver class for controlling the backlight brightness
 *        of an LCD via PWM.
 */

#ifndef St7735DisplayBrightnessDriver_H_
#define St7735DisplayBrightnessDriver_H_

#include "Driver/Interfaces/IDisplayBrightnessDriver.hpp"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

#include <cstdint>

namespace Driver
{
    /**
     * @class St7735DisplayBrightnessDriver
     * @brief Handles the backlight level of the LCD using Pulse Width Modulation (PWM).
     *
     * This class provides methods to initialize and control the brightness of an LCD backlight.
     * It interfaces with the hardware using PWM signals to adjust the brightness level.
     *
     * The PWM frequency is set to 5 kHz.
     */
    class St7735DisplayBrightnessDriver : public IDisplayBrightnessDriver
    {
    public:
        /**
         * @brief Constructor for St7735DisplayBrightnessDriver.
         * @param htim Reference to a TIM_HandleTypeDef structure that contains
         *             the configuration information for TIM module.
         */
        explicit St7735DisplayBrightnessDriver(TIM_HandleTypeDef &htim);

        /**
         * @brief Default constructor for St7735DisplayBrightnessDriver.
         *
         * Deleted to prevent creation without a valid timer handle.
         */
        St7735DisplayBrightnessDriver() = delete;

        /**
         * @brief Default destructor for St7735DisplayBrightnessDriver.
         */
        ~St7735DisplayBrightnessDriver() override = default;

        // Delete copy constructor and assignment operator

        /**
         * @brief Copy constructor for St7735DisplayBrightnessDriver.
         *
         * Deleted to prevent copying of the driver instance.
         */
        St7735DisplayBrightnessDriver(const St7735DisplayBrightnessDriver &) = delete;

        /**
         * @brief Copy assignment operator for St7735DisplayBrightnessDriver.
         *
         * Deleted to prevent assignment of the driver instance.
         */
        St7735DisplayBrightnessDriver &operator=(const St7735DisplayBrightnessDriver &) = delete;

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
        bool setBrightness(BrightnessPercentage brightness) override;

    private:
        /**
         * @brief Initializes the timer used for PWM.
         *
         * Configures the timer with the appropriate prescaler, period, and other settings for PWM operation.
         *
         * @return True if the timer is initialized successfully, false otherwise.
         */
        bool initializeTimer();

        /**
         * @brief Configures the PWM channel for brightness control.
         *
         * Sets up the PWM channel with the appropriate settings for PWM signal generation.
         *
         * @return True if the PWM channel is configured successfully, false otherwise.
         */
        bool configurePWMChannel();

        /**
         * @brief Starts the PWM with an initial brightness setting.
         *
         * Begins PWM signal generation and sets the initial brightness level.
         *
         * @return True if the PWM starts successfully, false otherwise.
         */
        bool startPWMWithInitialBrightness();

        /**
         * @brief Stops the PWM signal controlling the display backlight.
         *
         * This method stops the PWM generation on the designated timer channel,
         * effectively turning off or dimming the backlight of the display depending on
         * the last PWM state before stop. It is used when the display is no
         * longer needed, or to save power when the backlight is not required.
         *
         * @return bool True if the PWM was successfully stopped, false if there was an error.
         *              The method returns false if the HAL function to stop the PWM fails.
         */
        bool stopPWM();

        /**
         * @brief Calculates the pulse width from the brightness percentage.
         *
         * Converts a brightness level in percentage to the corresponding PWM pulse width.
         *
         * @param brightness Brightness level as a percentage (0-100).
         * @return The pulse width corresponding to the given brightness level.
         */
        [[nodiscard]] static std::uint32_t calculatePulseFromBrightness(BrightnessPercentage brightness);

        /// Initial brightness level, set to 0% by default.
        const BrightnessPercentage initialBrightness{0u};

        /// Maximum brightness level, set to 100% by default.
        const BrightnessPercentage MaxBrightness{100u};

        /// Reference to the timer handle used for PWM.
        TIM_HandleTypeDef &htim;
    };

}

#endif // St7735DisplayBrightnessDriver_H_
