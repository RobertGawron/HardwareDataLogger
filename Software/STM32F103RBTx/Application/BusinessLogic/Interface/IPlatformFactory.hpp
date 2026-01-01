/**
 * @file IPlatformFactory.hpp
 * @brief Declaration of the IPlatformFactory interface for creating platform-specific drivers.
 *
 * This file contains the declaration of the IPlatformFactory interface, which provides methods
 * for creating instances of various platform-specific drivers used in the application.
 * These drivers include ambient light sensors, display brightness controllers, display drivers,
 * keyboard drivers, UART drivers, and SD card drivers.
 */

#ifndef IPlatformFactory_h
#define IPlatformFactory_h

#include "Driver/Interface/IAmbientLightSensorDriver.hpp"
#include "Driver/Interface/IDisplayBrightnessDriver.hpp"
#include "Driver/Interface/IDisplayDriver.hpp"
#include "Driver/Interface/IKeyboardDriver.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"
#include "Driver/Interface/UartId.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/PulseCounterId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

namespace BusinessLogic
{
    /**
     * @class IPlatformFactory
     * @brief Interface for creating platform-specific driver instances.
     *
     * The IPlatformFactory class provides an interface for creating various driver instances that
     * are platform-specific. These drivers interact with different hardware components, such as
     * ambient light sensors, displays, keyboards, UART communication interfaces, and SD cards.
     * Platform-specific factories implement this interface to supply appropriate driver instances
     * for the target platform.
     */
    class IPlatformFactory
    {
    public:
        /**
         * @brief Default constructor for IPlatformFactory.
         */
        IPlatformFactory() = default;

        /**
         * @brief Virtual destructor for IPlatformFactory.
         *
         * Ensures proper cleanup of resources for derived classes.
         */
        virtual ~IPlatformFactory() = default;

        /**
         * @brief gets an instance of the ambient light sensor driver.
         *
         * Provides a platform-specific implementation of the ambient light sensor driver.
         *
         * @return A reference to the platform-specific ambient light sensor driver.
         */
        virtual Driver::IAmbientLightSensorDriver &getAmbientLightSensorDriver() = 0;

        /**
         * @brief gets an instance of the display brightness driver.
         *
         * Provides a platform-specific implementation of the display brightness driver.
         *
         * @return A reference to the platform-specific display brightness driver.
         */
        virtual Driver::IDisplayBrightnessDriver &getDisplayBrightnessDriver() = 0;

        /**
         * @brief gets an instance of the display driver.
         *
         * Provides a platform-specific implementation of the display driver.
         *
         * @return A reference to the platform-specific display driver.
         */
        virtual Driver::IDisplayDriver &getDisplayDriver() = 0;

        /**
         * @brief gets an instance of the keyboard driver.
         *
         * Provides a platform-specific implementation of the keyboard driver.
         *
         * @return A reference to the platform-specific keyboard driver.
         */
        virtual Driver::IKeyboardDriver &getKeyboardDriver() = 0;

        /**
         * @brief gets an instance of the UART driver.
         *
         * Provides a platform-specific implementation of the UART driver.
         *
         * @param deviceId The identifier for the specific UART instance to get.
         * @return A reference to the platform-specific UART driver.
         */
        virtual Driver::IUartDriver &getUartDriver(Driver::UartId deviceId) = 0;

        /**
         * @brief gets an instance of the SD card driver.
         *
         * Provides a platform-specific implementation of the SD card driver.
         *
         * @return A reference to the platform-specific SD card driver.
         */
        virtual Driver::ISdCardDriver &getSdCardDriver() = 0;

        /**
         * @brief gets an instance of the pulse counter driver.
         *
         * Provides a platform-specific implementation of the pulse counter driver.
         *
         * @param deviceId The identifier for the specific pulse counter instance to get.
         * @return A reference to the platform-specific pulse counter driver.
         */
        virtual Driver::IPulseCounterDriver &getPulseCounterDriver(Driver::PulseCounterId deviceId) = 0;
    };
}

#endif // IPlatformFactory_h
