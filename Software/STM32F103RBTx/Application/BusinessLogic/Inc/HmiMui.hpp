#ifndef HmiMui_h
#define HmiMui_h

/**
 * @file HmiMui.hpp
 * @brief Declaration of the HmiMui class implementing IHmi with MUI/U8g2.
 */

#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
#include "BusinessLogic/Interfaces/IHmi.hpp"
#include "U8g2lib.h"
#include "MUIU8g2.h"

namespace BusinessLogic
{
    /**
     * @class HmiMui
     * @brief MUI/U8g2-based implementation of the Human-Machine Interface.
     *
     * Provides graphical UI using MUI framework and U8g2 display library.
     * Manages display rendering, brightness control, and user input.
     */
    class HmiMui : public IHmi
    {
    public:
        /**
         * @brief Constructs HmiMui with required components.
         * @param hmiMeasurementModel Measurement model for UI data
         * @param display Display rendering interface
         * @param displayBrightnessRegulator Display brightness controller
         * @param keyboard User input interface
         */
        HmiMui(HmiMeasurementModel &hmiMeasurementModel,
               Device::IDisplay &display,
               Device::IDisplayBrightnessRegulator &displayBrightnessRegulator,
               Device::IKeyboard &keyboard);

        /** @brief Deleted default constructor */
        HmiMui() = delete;
        
        /** @brief Default virtual destructor */
        ~HmiMui() override = default;
        
        /** @brief Deleted copy constructor */
        HmiMui(const HmiMui &) = delete;
        
        /** @brief Deleted copy assignment operator */
        HmiMui &operator=(const HmiMui &) = delete;

        /**
         * @brief Initializes HMI components.
         * @return true if successful, false otherwise
         */
        bool initialize() override;

        /**
         * @brief Starts HMI operation.
         * @return true if successful, false otherwise
         */
        bool start() override;

        /**
         * @brief Processes periodic updates.
         * @return true if successful, false otherwise
         */
        bool tick() override;

    private:
        HmiMeasurementModel &hmiMeasurementModel;      ///< Measurement data provider
        Device::IDisplay &display;                     ///< Display rendering interface
        Device::IDisplayBrightnessRegulator &displayBrightnessRegulator; ///< Brightness controller
        Device::IKeyboard &keyboard;                   ///< User input handler
        MUIU8G2 mui;                                   ///< MUI framework instance
    };
}

#endif // HmiMui_h
