/**
 * @file IHmiFactory.hpp
 * @brief Defines the IHmiFactory interface for creating HMI-related components.
 */

#ifndef IHmiFactory_h
#define IHmiFactory_h

#include "Device/Interfaces/IKeyboard.hpp"
#include "Device/Inc/DisplayBrightnessRegulator.hpp"
#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Driver/Interfaces/IDisplayDriver.hpp"

namespace BusinessLogic
{
    /**
     * @class IHmiFactory
     * @brief Interface for creating Human-Machine Interface (HMI)-related components.
     *
     * The IHmiFactory class provides an interface for creating and initializing various
     * HMI-related components such as displays, keyboards, and brightness regulators.
     * This abstraction allows for flexible and modular creation of platform-specific
     * HMI components.
     */
    class IHmiFactory
    {
    public:
        /**
         * @brief Constructs an IHmiFactory instance.
         */
        IHmiFactory() = default;

        /**
         * @brief Virtual destructor for IHmiFactory.
         *
         * Ensures proper cleanup of resources for derived classes.
         */
        virtual ~IHmiFactory() = default;

        /**
         * @brief Initializes the HMI factory.
         *
         * This method prepares the factory to create and manage HMI components.
         *
         * @return True if initialization was successful; false otherwise.
         */
        virtual bool initialize() = 0;

        /**
         * @brief Starts the HMI factory.
         *
         * This method starts the operation of all HMI components created by the factory.
         *
         * @return True if the operation started successfully; false otherwise.
         */
        virtual bool start() = 0;

        /**
         * @brief Periodic update function for the HMI factory.
         *
         * This method should be called periodically to update the state of HMI components.
         *
         * @return True if the update operation was successful; false otherwise.
         */
        virtual bool tick() = 0;

        virtual bool addDataSource(Device::IMeasurementRecorder &recorder) = 0;
    };
}

#endif // IHmiFactory_h
