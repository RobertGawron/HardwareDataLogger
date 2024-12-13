/**
 * @file IHmi.hpp
 * @brief Defines the IHmi interface, a base class for implementing Human-Machine Interface (HMI) functionality.
 */

#ifndef IHmi_h
#define IHmi_h

#include "Device/Interfaces/IKeyboard.hpp"
#include "Device/Interfaces/IDisplay.hpp"
#include "Device/Interfaces/IDisplayBrightnessRegulator.hpp"

namespace BusinessLogic
{
    /**
     * @class IHmi
     * @brief Interface for Human-Machine Interface (HMI) implementations.
     *
     * The IHmi class provides a base interface for implementing HMI functionality. It was originally designed
     * with the Model-View-Controller (MVC) pattern in mind. However, due to the capabilities of the MUI library,
     * the implementation was simplified, making it possible to avoid the full MVC structure.
     *
     * Derived classes from this interface are the primary users of the provided components: `IDisplay`,
     * `IDisplayBrightnessRegulator`, and `IKeyboard`. These components are injected via the constructor, and the
     * derived classes manage their usage.
     */
    class IHmi
    {
    public:
        /**
         * @brief Constructs an IHmi instance with the provided HMI components.
         *
         * @param display Reference to an `IDisplay` object used for rendering output.
         * @param displayBrightnessRegulator Reference to an `IDisplayBrightnessRegulator` object
         *                                    for managing display brightness levels.
         * @param keyboard Reference to an `IKeyboard` object used for handling user input.
         */
        IHmi(Device::IDisplay &display,
             Device::IDisplayBrightnessRegulator &displayBrightnessRegulator,
             Device::IKeyboard &keyboard) {}

        /**
         * @brief Virtual destructor for IHmi.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IHmi() = default;

        /**
         * @brief Initializes the HMI system.
         *
         * Prepares the HMI components for operation. This may include configuring the display,
         * setting up input handling, and initializing any necessary data structures.
         *
         * @return True if initialization was successful; false otherwise.
         */
        virtual bool initialize() = 0;

        /**
         * @brief Starts the HMI system.
         *
         * Begins operation of the HMI, enabling interaction and rendering.
         *
         * @return True if the HMI started successfully; false otherwise.
         */
        virtual bool start() = 0;

        /**
         * @brief Periodic update function for the HMI system.
         *
         * This method should be called periodically to handle input, update the display,
         * and perform other necessary tasks.
         *
         * @return True if the update operation was successful; false otherwise.
         */
        virtual bool tick() = 0;
    };
}

#endif // IHmi_h
