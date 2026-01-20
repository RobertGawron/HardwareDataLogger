/**
 * @file HmiFacade.cppm
 * @brief Human-Machine Interface managing display, input, and user interaction.
 */
module;

#include "U8g2lib.h"
#include "MUIU8g2.h"

export module BusinessLogic.HmiFacade;

import BusinessLogic.ApplicationComponent;

import Device;

export namespace BusinessLogic
{
    /**
     * @class HmiFacade
     * @brief Manages user interface rendering and input handling.
     * Coordinates display updates, brightness control, and keyboard events using
     * MUI graphical framework. Handles UI state and user interaction workflows.
     */
    class HmiFacade final : public ApplicationComponent
    {
    public:
        /**
         * @brief Constructs interface with hardware component references.
         * @param display Renders graphical content to screen.
         * @param displayBrightness Controls backlight intensity.
         * @param keyboard Captures user button presses and input events.
         */
        HmiFacade(Device::Display &display,
                  Device::DisplayBrightness &displayBrightness,
                  Device::Keyboard &keyboard);

        HmiFacade() = delete;
        ~HmiFacade() = default;
        HmiFacade(const HmiFacade &) = delete;
        HmiFacade &operator=(const HmiFacade &) = delete;

        /**
         * @brief Initializes MUI framework and display subsystems.
         * @return true if UI framework and hardware initialized successfully.
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Activates display and prepares UI for user interaction.
         * @return true if display enabled and ready for rendering.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Processes input events and updates display content.
         * @return true if frame rendered and input processed successfully.
         */
        [[nodiscard]] auto onTick() noexcept -> bool;

        /**
         * @brief Legacy periodic update method.
         * @return true if update successful.
         * @deprecated Use onTick() instead for lifecycle-managed execution.
         */
        // bool tick();

    private:
        Device::Display &display;
        Device::DisplayBrightness &displayBrightness;
        Device::Keyboard &keyboard;
        MUIU8G2 mui; ///< MUI graphical framework instance
    };
}