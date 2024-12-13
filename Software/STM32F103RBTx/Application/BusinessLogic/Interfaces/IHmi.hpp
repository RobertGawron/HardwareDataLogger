#ifndef IHmi_h
#define IHmi_h

#include "Device/Interfaces/IKeyboard.hpp"
#include "Device/Interfaces/IDisplay.hpp"
#include "Device/Interfaces/IDisplayBrightnessRegulator.hpp"

namespace BusinessLogic
{

    class IHmi
    {
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes a new instance of the IHmi interface.
         */
        IHmi(Device::IDisplay &display,
             Device::IDisplayBrightnessRegulator &displayBrightnessRegulator,
             Device::IKeyboard &keyboard) {}

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IHmi() = default;

        virtual bool initialize() = 0;
        virtual bool start() = 0;

        virtual bool tick() = 0;
    };
}

#endif