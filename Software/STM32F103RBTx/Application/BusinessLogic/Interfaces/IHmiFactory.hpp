#ifndef IHmiFactory_h
#define IHmiFactory_h

#include "Device/Interfaces/IKeyboard.hpp"
#include "Driver/Interfaces/IDisplayDriver.hpp"
// #include "Device/Interfaces/IDisplayBrightnessRegulator.hpp"
#include "Device/Inc/DisplayBrightnessRegulator.hpp"

namespace BusinessLogic
{
    /**
     * @class IHmiFactory
     * @brief Interface for creating HMI-related components.
     *

     */
    class IHmiFactory
    {
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes a new instance of the IHmiFactory interface.
         */
        IHmiFactory() = default;

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IHmiFactory() = default;

        virtual bool initialize() = 0;
        virtual bool start() = 0;

        virtual bool tick() = 0;

#if 0 
    private:
        /**
         * @brief Retrieves the display driver.
         *
         * This method returns a reference to the display driver. The display driver is responsible for rendering
         * graphical content on the display.
         *
         * @return Driver::IDisplayDriver& Reference to the display driver.
         */
        virtual Driver::IDisplayDriver &getDisplay() = 0;

        /**
         * @brief Retrieves the display brightness regulator.
         *
         * This method returns a reference to the display brightness regulator. The brightness regulator manages
         * the brightness settings of the display.
         *
         * @return Device::IDisplayBrightnessRegulator& Reference to the display brightness regulator.
         */
        virtual Device::IDisplayBrightnessRegulator &getDisplayBrightnessRegulator() = 0;

        /**
         * @brief Retrieves the keyboard.
         *
         * This method returns a reference to the keyboard component. The keyboard component is responsible for
         * handling keyboard input.
         *
         * @return Device::IKeyboard& Reference to the keyboard.
         */
        virtual Device::IKeyboard &getKeyboard() = 0;
#endif
    };
}

#endif // IHmiFactory_h