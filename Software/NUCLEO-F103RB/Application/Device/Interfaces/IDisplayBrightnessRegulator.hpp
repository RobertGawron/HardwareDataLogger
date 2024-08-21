#ifndef IDisplayBrightnessRegulator_h
#define IDisplayBrightnessRegulator_h

#include "IAmbientLightSensorDriver.hpp"
#include "IDisplayBrightnessDriver.hpp"

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
        /**
         * @brief Default constructor.
         *
         * Initializes an instance of IDisplayBrightnessRegulator. The default constructor does not perform any
         * specific initialization.
         */
        explicit IDisplayBrightnessRegulator() = default;

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes. The destructor is virtual to support polymorphic deletion.
         */
        virtual ~IDisplayBrightnessRegulator() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         *
         * Prevents copying of IDisplayBrightnessRegulator instances.
         */
        IDisplayBrightnessRegulator(const IDisplayBrightnessRegulator &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent copying.
         *
         * Prevents assignment of IDisplayBrightnessRegulator instances.
         * @return IDisplayBrightnessRegulator& Reference to this object.
         */
        IDisplayBrightnessRegulator &operator=(const IDisplayBrightnessRegulator &) = delete;
        virtual bool init() = 0;
        /**
         * @brief Ticks the brightness regulator state machine.
         *
         * This method should be called periodically to update the brightness level based on ambient light changes
         * and user preferences.
         */
        virtual void tick() = 0;

        /**
         * @brief Gets the current brightness level as a percentage.
         *
         * This method returns the current brightness level of the display as a percentage.
         *
         * @return The brightness level as a percentage (0-100).
         */
        virtual uint8_t getBrightnessPercentage() const = 0;

        /**
         * @brief Sets the brightness level as a percentage.
         *
         * This method sets the brightness level of the display to a specific percentage.
         *
         * @param level The brightness level to set, in percentage (0-100).
         */
        virtual void setBrightnessPercentage(uint8_t level) = 0;
    };

}

#endif //  IDisplayBrightnessRegulator_h