#ifndef HmiFacade_h
#define HmiFacade_h

/**
 * @file HmiFacade.hpp
 * @brief Declaration of the HmiFacade class implementing IHmi with MUI/U8g2.
 */

// #include "BusinessLogic/Interface/IPlatformFactory.hpp"
#include "BusinessLogic/Inc/ApplicationComponent.hpp"

#include "Device/Inc/Display.hpp"
#include "Device/Inc/DisplayBrightness.hpp"
#include "Device/Inc/Keyboard.hpp"

#include "U8g2lib.h"
#include "MUIU8g2.h"

namespace BusinessLogic
{
    /**
     * @class HmiFacade
     * @brief MUI/U8g2-based implementation of the Human-Machine Interface.
     *
     * Provides graphical UI using MUI framework and U8g2 display library.
     * Manages display rendering, brightness control, and user input.
     */
    class HmiFacade final : public ApplicationComponent
    {
    public:
        /**
         * @brief Constructs HmiFacade with required components.
         * @param display Display rendering interface
         * @param displayBrightnessRegulator Display brightness controller
         * @param keyboard User input interface
         */
        HmiFacade(Device::Display &display,
                  Device::DisplayBrightness &displayBrightnessRegulator,
                  Device::Keyboard &keyboard);

        /** @brief Deleted default constructor */
        HmiFacade() = delete;

        /** @brief Default virtual destructor */
        ~HmiFacade() = default;

        /** @brief Deleted copy constructor */
        HmiFacade(const HmiFacade &) = delete;

        /** @brief Deleted copy assignment operator */
        HmiFacade &operator=(const HmiFacade &) = delete;

        // Lifecycle hooks (called by base class)
        [[nodiscard]] bool onInit() noexcept;
        [[nodiscard]] bool onStart() noexcept;
        [[nodiscard]] bool onTick() noexcept;
        // [[nodiscard]] bool onStop() noexcept;

        /**
         * @brief Processes periodic updates.
         * @return true if successful, false otherwise
         */
        bool tick();

    private:
        //  HmiMeasurementModel &hmiMeasurementModel;                        ///< Measurement data provider
        Device::Display &display;                              ///< Display rendering interface
        Device::DisplayBrightness &displayBrightnessRegulator; ///< Brightness controller
        Device::Keyboard &keyboard;                            ///< User input handler
        MUIU8G2 mui;                                           ///< MUI framework instance
    };
}

#endif // HmiFacade_h