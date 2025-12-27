#ifndef HmiFacade_h
#define HmiFacade_h

/**
 * @file HmiFacade.hpp
 * @brief Declaration of the HmiFacade class implementing IHmi with MUI/U8g2.
 */

// #include "BusinessLogic/Interface/IPlatformFactory.hpp"

#include "Device/Interface/IDisplay.hpp"
#include "Device/Interface/IDisplayBrightnessRegulator.hpp"
#include "Device/Interface/IKeyboard.hpp"

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
    class HmiFacade
    {
    public:
        /**
         * @brief Constructs HmiFacade with required components.
         * @param hmiMeasurementModel Measurement model for UI data
         * @param display Display rendering interface
         * @param displayBrightnessRegulator Display brightness controller
         * @param keyboard User input interface
         */
        HmiFacade( // HmiMeasurementModel &hmiMeasurementModel,
            Device::IDisplay &display,
            Device::IDisplayBrightnessRegulator &displayBrightnessRegulator,
            Device::IKeyboard &keyboard);

        /** @brief Deleted default constructor */
        HmiFacade() = delete;

        /** @brief Default virtual destructor */
        ~HmiFacade() = default;

        /** @brief Deleted copy constructor */
        HmiFacade(const HmiFacade &) = delete;

        /** @brief Deleted copy assignment operator */
        HmiFacade &operator=(const HmiFacade &) = delete;

        /**
         * @brief Initializes HMI components.
         * @return true if successful, false otherwise
         */
        bool initialize();

        /**
         * @brief Starts HMI operation.
         * @return true if successful, false otherwise
         */
        bool start();

        /**
         * @brief Processes periodic updates.
         * @return true if successful, false otherwise
         */
        bool tick();

    private:
        //  HmiMeasurementModel &hmiMeasurementModel;                        ///< Measurement data provider
        Device::IDisplay &display;                                       ///< Display rendering interface
        Device::IDisplayBrightnessRegulator &displayBrightnessRegulator; ///< Brightness controller
        Device::IKeyboard &keyboard;                                     ///< User input handler
        MUIU8G2 mui;                                                     ///< MUI framework instance
    };
}

#endif // HmiFacade_h
