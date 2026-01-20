/**
 * @file ApplicationFacade.cppm
 * @brief Application component orchestrator managing initialization and coordination.
 */
module;

#include <array>
#include <cstddef>
#include <functional>
#include <utility>

export module BusinessLogic.ApplicationFacade;

import BusinessLogic.ApplicationComponent;
import BusinessLogic.MeasurementCoordinator;
import BusinessLogic.HmiFacade;

import Device;

import Driver.PlatformFactory;

export namespace BusinessLogic
{
    /**
     * @class ApplicationFacade
     * @brief Top-level coordinator managing application subsystems and their lifecycles.
     * Owns and initializes measurement sources, data recorders, HMI components, and
     * the coordinator that routes data between them. Ensures components are initialized
     * in correct dependency order and coordinates their operational state transitions.
     */
    class ApplicationFacade final : public ApplicationComponent
    {
    public:
        /**
         * @brief Constructs application with platform-specific drivers.
         * @param factory Provides hardware drivers for peripheral initialization.
         */
        explicit ApplicationFacade(Driver::PlatformFactory &factory) noexcept;

        ~ApplicationFacade() = default;

        ApplicationFacade() = delete;
        ApplicationFacade(const ApplicationFacade &) = delete;
        ApplicationFacade(ApplicationFacade &&) = delete;
        ApplicationFacade &operator=(const ApplicationFacade &) = delete;
        ApplicationFacade &operator=(ApplicationFacade &&) = delete;

        /**
         * @brief Initializes all subsystems in dependency order.
         * @return true if all sources, recorders, HMI, and coordinator initialized successfully.
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Starts all subsystems for operational mode.
         * @return true if all components transitioned to running state successfully.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Stops all subsystems, halting data acquisition and recording.
         * @return true if all components stopped cleanly.
         */
        [[nodiscard]] auto onStop() noexcept -> bool;

        /**
         * @brief Executes one iteration of all active subsystems.
         * @return true if all subsystem tick operations completed successfully.
         */
        [[nodiscard]] auto onTick() noexcept -> bool;

    private:
        static constexpr std::size_t SOURCES_COUNT{
            std::to_underlying(Device::MeasurementDeviceId::LAST_NOT_USED)};
        static constexpr std::size_t RECORDERS_COUNT{2};

        // Measurement sources (data producers)
        Device::PulseCounterSource pulseCounter1;
        Device::PulseCounterSource pulseCounter2;
        Device::PulseCounterSource pulseCounter3;
        Device::PulseCounterSource pulseCounter4;
        Device::UartSource uartReceiver;

        std::array<Device::SourceVariant, SOURCES_COUNT> sources;

        // Data recorders (data consumers)
        Device::WiFiRecorder wifiRecorder;
        Device::SdCardRecorder sdCardRecorder;
        std::array<Device::RecorderVariant, RECORDERS_COUNT> recorders;

        // Data routing
        MeasurementCoordinator<SOURCES_COUNT, RECORDERS_COUNT> measurement;

        // Human-Machine Interface
        Device::Display display;
        Device::DisplayBrightness brightness;
        Device::Keyboard keyboard;
        BusinessLogic::HmiFacade hmi;
    };

} // namespace BusinessLogic
