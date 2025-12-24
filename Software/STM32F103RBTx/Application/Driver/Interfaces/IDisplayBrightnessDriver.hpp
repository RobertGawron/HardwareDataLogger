/**
 * @file IDisplayBrightnessDriver.hpp
 * @brief Defines the IDisplayBrightnessDriver interface for controlling display brightness.
 */

#ifndef IDisplayBrightnessDriver_H_
#define IDisplayBrightnessDriver_H_

#include <cstdint>
#include "Driver/Interfaces/DriverState.hpp"

namespace Driver
{

    /**
     * @class IDisplayBrightnessDriver
     * @brief Interface for display brightness control drivers.
     *
     * This interface provides a set of pure virtual functions that must be implemented
     * by any display brightness driver. It includes basic operations for initializing the driver,
     * setting the brightness level, and retrieving the current brightness level.
     */
    class IDisplayBrightnessDriver : public DriverState
    {
    public:
        /** @brief Typedef for brightness level represented as a percentage (0-100). */
        using BrightnessPercentage = std::uint8_t;

        /**
         * @brief Default constructor for IDisplayBrightnessDriver.
         */
        IDisplayBrightnessDriver() = default;

        /**
         * @brief Virtual destructor for IDisplayBrightnessDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IDisplayBrightnessDriver() override = default;

        /**
         * @brief Deleted copy constructor.
         *
         * This prevents copying of the driver interface to avoid accidental duplication
         * of the driver instance.
         *
         * @param other The other IDisplayBrightnessDriver object to copy from (deleted).
         */
        IDisplayBrightnessDriver(const IDisplayBrightnessDriver &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         *
         * This prevents assignment of the driver interface to avoid accidental duplication
         * of the driver instance.
         *
         * @param other The other IDisplayBrightnessDriver object to assign from (deleted).
         * @return Reference to this object (deleted).
         */
        IDisplayBrightnessDriver &operator=(const IDisplayBrightnessDriver &) = delete;

        /**
         * @brief Sets the display brightness.
         *
         * This function sets the brightness of the display to a specified value.
         *
         * @param value The brightness level to set, as a percentage (0-100).
         * @return True if the brightness was successfully set, false otherwise.
         */
        virtual bool setBrightness(BrightnessPercentage value) = 0;
    };

}

#endif // IDisplayBrightnessDriver_H_
