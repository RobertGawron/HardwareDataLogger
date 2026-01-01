#ifndef IDISPLAY_BRIGHTNESS_REGULATOR_HPP
#define IDISPLAY_BRIGHTNESS_REGULATOR_HPP

/**
 * @file IDisplayBrightnessRegulator.hpp
 * @brief Declaration of the IDisplayBrightnessRegulator interface for managing display brightness.
 *
 * This file contains the declaration of the IDisplayBrightnessRegulator interface, which defines methods
 * for controlling and regulating the brightness of a display based on ambient light levels and user preferences.
 */

#include <cstdint>

namespace Device
{
    /**
     * @class IDisplayBrightnessRegulator
     * @brief Interface for regulating display brightness based on ambient light and user preferences.
     *
     * The IDisplayBrightnessRegulator class defines an interface for controlling the brightness of a display
     * based on ambient light sensor inputs and user settings. It provides methods for initializing the regulator,
     * updating its state, and getting or setting the brightness level.
     */
    class IDisplayBrightnessRegulator
    {
    public:
        constexpr IDisplayBrightnessRegulator() noexcept = default;
        virtual ~IDisplayBrightnessRegulator() = default;

        // Non-copyable and non-movable
        IDisplayBrightnessRegulator(const IDisplayBrightnessRegulator &) = delete;
        IDisplayBrightnessRegulator(IDisplayBrightnessRegulator &&) = delete;
        IDisplayBrightnessRegulator &operator=(const IDisplayBrightnessRegulator &) = delete;
        IDisplayBrightnessRegulator &operator=(IDisplayBrightnessRegulator &&) = delete;

        /**
         * @brief Initializes the brightness regulator.
         *
         * Sets up necessary configurations for the brightness regulator.
         *
         * @return True if initialization is successful; false otherwise.
         */
        [[nodiscard]] virtual bool init() noexcept = 0;

        /**
         * @brief Ticks the brightness regulator state machine.
         *
         * This method should be called periodically to update the brightness level based on ambient light changes
         * and user preferences. Implementations should perform light level sampling and brightness adjustment
         * in this method.
         */
        virtual void tick() noexcept = 0;

        /**
         * @brief Gets the current brightness level as a percentage.
         *
         * This method returns the current brightness level of the display as a percentage.
         *
         * @return The brightness level as a percentage (0-100).
         */
        [[nodiscard]] virtual std::uint8_t getBrightnessPercentage() const noexcept = 0;

        /**
         * @brief Sets the display brightness to a specific percentage.
         *
         * This method allows manual setting of the brightness level, overriding automatic regulation.
         *
         * @param level The desired brightness level (0-100%).
         * @return True if brightness was successfully set, false otherwise.
         */
        [[nodiscard]] virtual bool setBrightnessPercentage(std::uint8_t level) noexcept = 0;
    };

} // namespace Device

#endif // IDISPLAY_BRIGHTNESS_REGULATOR_HPP