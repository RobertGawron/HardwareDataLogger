/**
 * @file IAmbientLightSensorDriver.hpp
 * @brief Defines the IAmbientLightSensorDriver interface for ambient light sensors.
 */

#ifndef IAMBIENTLIGHTSENSORDRIVER_H_
#define IAMBIENTLIGHTSENSORDRIVER_H_

#include <cstdint>
#include "Driver/Inc/DriverState.hpp"

namespace Driver
{

    /**
     * @class IAmbientLightSensorDriver
     * @brief Interface for ambient light sensor drivers to interact with different light sensor hardware.
     *
     * This interface provides a set of pure virtual functions that must be implemented
     * by any ambient light sensor measurer driver. It includes basic operations like initializing the sensor
     * and retrieving the current ambient light level.
     */
    class IAmbientLightSensorDriver : public DriverState
    {
    public:
        IAmbientLightSensorDriver() = default;
        /**
         * @brief Virtual destructor for IAmbientLightSensorDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IAmbientLightSensorDriver() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        IAmbientLightSensorDriver(const IAmbientLightSensorDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return IAmbientLightSensorDriver& The assigned object.
         */
        IAmbientLightSensorDriver &operator=(const IAmbientLightSensorDriver &) = delete;

        /**
         * @brief Retrieves the current ambient light level.
         *
         * This function reads the current light level detected by the sensor. The value returned
         * represents the intensity of ambient light in a unit-specific format.
         *
         * @return The current ambient light level as a 32-bit unsigned integer.
         */
        [[nodiscard]] virtual std::uint32_t getAmbientLightLevel() const = 0;
    };

}

#endif // IAMBIENTLIGHTSENSORDRIVER_H_
