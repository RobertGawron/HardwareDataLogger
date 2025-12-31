/**
 * @file ApplicationBuilder.hpp
 * @brief Defines the ApplicationBuilder class responsible for orchestrating application component initialization.
 */

#ifndef ApplicationFacade_h
#define ApplicationFacade_h

#include "BusinessLogic/Interface/IApplicationFacade.hpp"
#include "BusinessLogic/Interface/IPlatformFactory.hpp"
#include "BusinessLogic/Inc/HmiFacade.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"

#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Device/Inc/UartMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/SdCardMeasurementRecorder.hpp"
#include "Device/Inc/Display.hpp"
#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/DisplayBrightnessRegulator.hpp"

#include "Driver/Interface/PulseCounterId.hpp"

#include <functional> // for std::reference_wrapper

namespace Device
{
    // Forward declarations
    class IMeasurementSource;
    class IMeasurementRecorder;
}

namespace BusinessLogic
{
    /**
     * @brief Orchestrates construction and initialization of core application components.
     *
     * Implements the facade pattern to coordinate initialization and registration of:
     * - Measurement sources (data producers)
     * - Data stores (data consumers)
     * - Human-Machine Interface (HMI)
     * - Core coordination mechanisms
     *
     */
    class ApplicationFacade : public IApplicationFacade
    {
    public:
        explicit ApplicationFacade(IPlatformFactory &factory);

        /**
         * @brief Deleted default constructor.
         */
        ApplicationFacade() = delete;

        /**
         * @brief Default destructor.
         */
        ~ApplicationFacade() override = default;

        /**
         * @brief Deleted copy constructor.
         */
        ApplicationFacade(const ApplicationFacade &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        ApplicationFacade &operator=(const ApplicationFacade &) = delete;

        /**
         * @brief Initializes all application components.
         *
         * Calls initialize() on all managed factories and components.
         *
         * @return true if all components initialized successfully, false otherwise
         */
        bool initialize() override;

        /**
         * @brief Starts all application components.
         * @return true if all components started successfully, false otherwise
         */
        bool start() override;

        /**
         * @brief Stops all application components.
         * @return true if all components stopped successfully, false otherwise
         */
        bool stop() override;

        /**
         * @brief Performs periodic update of application components.
         * @return true if tick was processed successfully, false otherwise
         */
        bool tick() override;

    private:
        Device::PulseCounterMeasurementSource pulseCounter1;
        Device::PulseCounterMeasurementSource pulseCounter2;
        Device::PulseCounterMeasurementSource pulseCounter3;
        Device::PulseCounterMeasurementSource pulseCounter4;

        Device::UartMeasurementSource uartReceiver;

        static constexpr std::size_t SourcesAmount{static_cast<std::size_t>(Device::MeasurementDeviceId::LAST_NOT_USED)};

        std::array<std::reference_wrapper<Device::IMeasurementSource>, SourcesAmount> sources;

        // recorders

        /** @brief WiFi measurement recorder instance */
        Device::WiFiMeasurementRecorder wifiRecorder;

        /** @brief SD card measurement recorder instance */
        Device::SdCardMeasurementRecorder sdCardRecorder;

        static constexpr std::size_t RecordersAmount = 2u;
        std::array<std::reference_wrapper<Device::IMeasurementRecorder>, RecordersAmount> recorders;

        MeasurementCoordinator<SourcesAmount, RecordersAmount> measurementCoordinator;
        // hmi

        /** @brief Display controller implementation */
        Device::Display display;

        /** @brief Display brightness regulator */
        Device::DisplayBrightnessRegulator brightnessRegulator;

        /** @brief User input handler */
        Device::Keyboard keyboard;

        BusinessLogic::HmiFacade hmi;
    };
}

#endif
