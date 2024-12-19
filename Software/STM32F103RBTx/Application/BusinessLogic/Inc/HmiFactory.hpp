#ifndef HmiFactory_h
#define HmiFactory_h

#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
#include "BusinessLogic/Interfaces/IHmiFactory.hpp"
#include "BusinessLogic/Inc/HmiMui.hpp"
#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Device/Inc/Display.hpp"
#include "Device/Inc/Keyboard.hpp"

namespace BusinessLogic
{
    /**
     * @class HmiFactory
     * @brief Factory class for creating HMI-related objects.
     *
     * The HmiFactory class is responsible for creating all Human-Machine Interface (HMI) related components.
     * It collaborates with the HmiBuilder to construct and provide instances of various components required
     * for the HMI system. This includes components such as data models, input controllers, view managers,
     * and platform-specific drivers.
     *
     * The factory pattern centralizes the creation logic of these components and manages their lifecycle.
     * This class implements the IHmiFactory interface and provides high-level methods for initializing
     * and managing the HMI system.
     */
    class HmiFactory : public IHmiFactory
    {
    public:
        /**
         * @brief Constructs an HmiFactory instance.
         *
         * @param platformFactory Reference to an IPlatformFactory instance used for creating platform-specific
         *                        components and drivers.
         */
        explicit HmiFactory(Device::IMeasurementReader &reader, IPlatformFactory &platformFactory);

        /**
         * @brief Deleted default constructor.
         *
         * Prevents the creation of HmiFactory instances without a platformFactory.
         */
        HmiFactory() = delete;

        /**
         * @brief Default destructor for HmiFactory.
         */
        ~HmiFactory() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying of HmiFactory.
         */
        HmiFactory(const HmiFactory &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment of HmiFactory.
         *
         * @return Reference to the HmiFactory instance.
         */
        HmiFactory &operator=(const HmiFactory &) = delete;

        /**
         * @brief Initializes the HMI system components.
         *
         * This method sets up all necessary components and prepares the HMI system for operation.
         *
         * @return true if initialization is successful, false otherwise.
         */
        bool initialize() override;

        /**
         * @brief Starts the HMI system.
         *
         * This method begins the operation of the HMI system and its components.
         *
         * @return true if the system starts successfully, false otherwise.
         */
        bool start() override;

        /**
         * @brief Provides periodic updates to the HMI system.
         *
         * This method is called periodically to update the HMI state.
         *
         * @return true if the tick operation is successful, false otherwise.
         */
        bool tick() override;

    private:
        HmiMeasurementModel hmiMeasurementModel;

        /**
         * @brief Display driver used by the HMI system.
         */
        Device::Display display;

        /**
         * @brief Display brightness regulator for managing screen brightness.
         */
        Device::DisplayBrightnessRegulator brightnessRegulator;

        /**
         * @brief Keyboard driver used for input in the HMI system.
         */
        Device::Keyboard keyboard;

        /**
         * @brief Instance of HMI implementation using the MUI library.
         *
         * Note: While directly exposing the use of the MUI library in the header file is not ideal, it is
         * necessary here due to design constraints.
         */
        HmiMui hmi;
    };
}

#endif // HmiFactory_h
