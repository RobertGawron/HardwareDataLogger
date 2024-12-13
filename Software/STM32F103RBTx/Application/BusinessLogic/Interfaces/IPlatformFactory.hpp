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

#include "Driver/Interfaces/IAmbientLightSensorDriver.hpp"
#include "Driver/Interfaces/IDisplayBrightnessDriver.hpp"
#include "Driver/Interfaces/IDisplayDriver.hpp"
#include "Driver/Interfaces/IKeyboardDriver.hpp"
#include "Driver/Interfaces/ISdCardDriver.hpp"
#include "Driver/Inc/UartIdentifier.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"
#include "Driver/Inc/PulseCounterIdentifier.hpp"
#include "Driver/Interfaces/IPulseCounterDriver.hpp"

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
         * @brief Creates an instance of the ambient light sensor driver.
         *
         * Provides a platform-specific implementation of the ambient light sensor driver.
         *
         * @return A reference to the platform-specific ambient light sensor driver.
         */
        virtual Driver::IAmbientLightSensorDriver &createAmbientLightSensorDriver() = 0;

        /**
         * @brief Creates an instance of the display brightness driver.
         *
         * Provides a platform-specific implementation of the display brightness driver.
         *
         * @return A reference to the platform-specific display brightness driver.
         */
        virtual Driver::IDisplayBrightnessDriver &createDisplayBrightnessDriver() = 0;

        /**
         * @brief Creates an instance of the display driver.
         *
         * Provides a platform-specific implementation of the display driver.
         *
         * @return A reference to the platform-specific display driver.
         */
        virtual Driver::IDisplayDriver &createDisplayDriver() = 0;

        /**
         * @brief Creates an instance of the keyboard driver.
         *
         * Provides a platform-specific implementation of the keyboard driver.
         *
         * @return A reference to the platform-specific keyboard driver.
         */
        virtual Driver::IKeyboardDriver &createKeyboardDriver() = 0;

        /**
         * @brief Creates an instance of the UART driver.
         *
         * Provides a platform-specific implementation of the UART driver.
         *
         * @param id The identifier for the specific UART instance to create.
         * @return A reference to the platform-specific UART driver.
         */
        virtual Driver::IUartDriver &createUartDriver(const Driver::UartIdentifier id) = 0;

        /**
         * @brief Creates an instance of the SD card driver.
         *
         * Provides a platform-specific implementation of the SD card driver.
         *
         * @return A reference to the platform-specific SD card driver.
         */
        virtual Driver::ISdCardDriver &createSdCardDriver() = 0;

        /**
         * @brief Creates an instance of the pulse counter driver.
         *
         * Provides a platform-specific implementation of the pulse counter driver.
         *
         * @param id The identifier for the specific pulse counter instance to create.
         * @return A reference to the platform-specific pulse counter driver.
         */
        virtual Driver::IPulseCounterDriver &createPulseCounterDriver(const Driver::PulseCounterIdentifier id) = 0;
    };
}

#endif // IPlatformFactory_h
