#ifndef HmiMui_h
#define HmiMui_h

/**
 * @file HmiMui.hpp
 * @brief Declaration of the HmiMui class, an implementation of the IHmi interface using the MUI and U8g2 libraries.
 *
 * This file contains the declaration of the HmiMui class, which integrates the MUI and U8g2 libraries
 * to provide a graphical user interface (GUI) for the Human-Machine Interface (HMI) system.
 */

#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
#include "BusinessLogic/Interfaces/IHmi.hpp"

#include "U8g2lib.h"
#include "MUIU8g2.h"

namespace BusinessLogic
{
    /**
     * @class HmiMui
     * @brief Implements the IHmi interface using MUI and U8g2 libraries.
     *
     * The HmiMui class provides an implementation of the IHmi interface, leveraging the MUI and U8g2
     * libraries to create and manage a graphical user interface. This class interacts with the
     * display, keyboard, and display brightness regulator to provide a seamless HMI experience.
     */
    class HmiMui : public IHmi
    {
    public:
        /**
         * @brief Constructs an HmiMui object with the required components.
         *
         * Initializes the HmiMui instance with references to the display, brightness regulator,
         * and keyboard components.
         *
         * @param display Reference to the display interface used for rendering graphical content.
         * @param displayBrightnessRegulator Reference to the brightness regulator for managing display brightness.
         * @param keyboard Reference to the keyboard interface for handling user input.
         */
        HmiMui(HmiMeasurementModel &hmiMeasurementModel,
               Device::IDisplay &display,
               Device::IDisplayBrightnessRegulator &displayBrightnessRegulator,
               Device::IKeyboard &keyboard);

        /**
         * @brief Deleted default constructor.
         *
         * Prevents instantiation of HmiMui without required component references.
         */
        HmiMui() = delete;

        /**
         * @brief Default virtual destructor.
         *
         * Ensures proper cleanup of the HmiMui instance and its resources.
         */
        ~HmiMui() override = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of HmiMui instances.
         */
        HmiMui(const HmiMui &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         *
         * Prevents assignment of HmiMui instances.
         * @return Reference to this object.
         */
        HmiMui &operator=(const HmiMui &) = delete;

        /**
         * @brief Initializes the HMI system.
         *
         * Prepares the HMI components for operation, including setting up the display and input handling.
         *
         * @return True if initialization was successful; false otherwise.
         */
        bool initialize() override;

        /**
         * @brief Starts the HMI system.
         *
         * Begins the operation of the HMI, enabling interaction and rendering.
         *
         * @return True if the HMI started successfully; false otherwise.
         */
        bool start() override;

        /**
         * @brief Periodic update function for the HMI system.
         *
         * This method should be called periodically to handle input, update the display, and perform other tasks.
         *
         * @return True if the tick operation was successful; false otherwise.
         */
        bool tick() override;

    private:
        HmiMeasurementModel &hmiMeasurementModel;

        Device::IDisplay &display;                                       /**< Reference to the display interface. */
        Device::IDisplayBrightnessRegulator &displayBrightnessRegulator; /**< Reference to the display brightness regulator. */
        Device::IKeyboard &keyboard;                                     /**< Reference to the keyboard interface. */

        MUIU8G2 mui; /**< Instance of the MUIU8G2 library for managing the GUI. */
    };
}

#endif // HmiMui_h
