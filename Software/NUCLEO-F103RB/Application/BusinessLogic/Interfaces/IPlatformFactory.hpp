#ifndef IPlatformFactory_h
#define IPlatformFactory_h

/**
 * @file IPlatformFactory.h
 * @brief Declaration of the IPlatformFactory interface for creating platform-specific drivers.
 *
 * This file contains the declaration of the IPlatformFactory interface, which provides methods
 * for creating instances of various platform-specific drivers used in the application.
 * These drivers include ambient light sensors, display brightness controllers, display drivers,
 * keyboard drivers, UART drivers, and SD card drivers.
 */

// Interface includes for various drivers, specific implementations are not included here.
#include "IAmbientLightSensorDriver.hpp"
#include "IDisplayBrightnessDriver.hpp"
#include "IDisplayDriver.hpp"
#include "IKeyboardDriver.hpp"
#include "ISdCardDriver.hpp"
#include "UartIdentifier.hpp"
#include "IUartDriver.hpp"
#include "PulseCounterIdentifier.hpp"
#include "IPulseCounterDriver.hpp"

namespace BusinessLogic
{
    /**
     * @class IPlatformFactory
     * @brief Interface for creating platform-specific driver instances.
     *
     * The IPlatformFactory class provides an interface for creating various driver instances that
     * are platform-specific. These drivers are used to interact with different hardware components
     * such as ambient light sensors, displays, keyboards, UART communication interfaces, and SD cards.
     * This interface is intended to be implemented by platform-specific factories that supply the
     * appropriate driver instances for the platform.
     */
    class IPlatformFactory
    {
    public:
        IPlatformFactory() = default;
        virtual ~IPlatformFactory() = default;

        /**
         * @brief Creates an instance of the ambient light sensor driver.
         *
         * This method should be implemented to return a reference to a platform-specific instance of
         * the IAmbientLightSensorDriver, which handles interaction with an ambient light sensor.
         *
         * @return A reference to the platform-specific ambient light sensor driver.
         */
        virtual Driver::IAmbientLightSensorDriver &createAmbientLightSensorDriver() = 0;

        /**
         * @brief Creates an instance of the display brightness driver.
         *
         * This method should be implemented to return a reference to a platform-specific instance of
         * the IDisplayBrightnessDriver, which handles controlling the brightness of a display.
         *
         * @return A reference to the platform-specific display brightness driver.
         */
        virtual Driver::IDisplayBrightnessDriver &createDisplayBrightnessDriver() = 0;

        /**
         * @brief Creates an instance of the display driver.
         *
         * This method should be implemented to return a reference to a platform-specific instance of
         * the IDisplayDriver, which handles display operations.
         *
         * @return A reference to the platform-specific display driver.
         */
        virtual Driver::IDisplayDriver &createDisplayDriver() = 0;

        /**
         * @brief Creates an instance of the keyboard driver.
         *
         * This method should be implemented to return a reference to a platform-specific instance of
         * the IKeyboardDriver, which handles keyboard input.
         *
         * @return A reference to the platform-specific keyboard driver.
         */
        virtual Driver::IKeyboardDriver &createKeyboardDriver() = 0;

        /**
         * @brief Creates an instance of the UART driver.
         *
         * This method should be implemented to return a reference to a platform-specific instance of
         * the IUartDriver, which handles UART communication.
         *
         * @param id The identifier for the UART to create.
         * @return A reference to the platform-specific UART driver.
         */
        virtual Driver::IUartDriver &createUartDriver(const Driver::UartIdentifier id) = 0;

        /**
         * @brief Creates an instance of the SD card driver.
         *
         * This method should be implemented to return a reference to a platform-specific instance of
         * the ISdCardDriver, which handles SD card operations.
         *
         * @return A reference to the platform-specific SD card driver.
         */
        virtual Driver::ISdCardDriver &createSdCardDriver() = 0;

        /**
         * @brief Creates an instance of the pulse counter driver.
         *
         * This method should be implemented to return a reference to a platform-specific instance of
         * the IPulseCounterDriver, which handles pulse counting for a specific pulse counter.
         *
         * @param id The identifier for the pulse counter to create.
         * @return A reference to the platform-specific pulse counter driver.
         */
        virtual Driver::IPulseCounterDriver &createPulseCounterDriver(const Driver::PulseCounterIdentifier id) = 0;
    };
}

#endif // IPlatformFactory_h
