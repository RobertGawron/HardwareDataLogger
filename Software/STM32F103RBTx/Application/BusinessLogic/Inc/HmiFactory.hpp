#ifndef HmiFactory_h
#define HmiFactory_h

#include "BusinessLogic/Interface/IPlatformFactory.hpp"
#include "BusinessLogic/Interface/IHmiFactory.hpp"
#include "BusinessLogic/Inc/HmiMui.hpp"
#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Device/Inc/Display.hpp"
#include "Device/Inc/Keyboard.hpp"

namespace BusinessLogic
{
    /**
     * @class HmiFactory
     * @brief Concrete factory for creating and managing HMI components.
     *
     * Constructs and initializes all Human-Machine Interface components including:
     * - Measurement data model
     * - Display controller
     * - Brightness regulator
     * - Input handler
     * - MUI-based interface implementation
     *
     * Implements the IHmiFactory interface for system integration.
     */
    class HmiFactory : public IHmiFactory
    {
    public:
        /**
         * @brief Constructs HmiFactory with required dependencies.
         * @param reader Measurement data reader for model initialization
         * @param platformFactory Platform-specific component factory
         */
        explicit HmiFactory(Device::IMeasurementReader &reader, IPlatformFactory &platformFactory);

        /** @brief Deleted default constructor */
        HmiFactory() = delete;

        /** @brief Default destructor */
        ~HmiFactory() override = default;

        /** @brief Deleted copy constructor */
        HmiFactory(const HmiFactory &) = delete;

        /** @brief Deleted copy assignment operator */
        HmiFactory &operator=(const HmiFactory &) = delete;

        /**
         * @brief Initializes all HMI components.
         * @return true if all components initialized successfully, false otherwise
         */
        bool initialize() override;

        /**
         * @brief Starts HMI system operation.
         * @return true if system started successfully, false otherwise
         */
        bool start() override;

        /**
         * @brief Processes periodic HMI updates.
         * @return true if update processed successfully, false otherwise
         */
        bool tick() override;

    private:
        /** @brief Measurement data model for HMI presentation */
        HmiMeasurementModel hmiMeasurementModel;

        /** @brief Display controller implementation */
        Device::Display display;

        /** @brief Display brightness regulator */
        Device::DisplayBrightnessRegulator brightnessRegulator;

        /** @brief User input handler */
        Device::Keyboard keyboard;

        /** @brief MUI-based HMI implementation */
        HmiMui hmi;
    };
}

#endif // HmiFactory_h
