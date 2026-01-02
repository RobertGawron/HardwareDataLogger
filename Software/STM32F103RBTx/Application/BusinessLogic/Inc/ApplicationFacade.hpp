/**
 * @file ApplicationFacade.hpp
 * @brief Defines the ApplicationFacade class responsible for orchestrating application component initialization.
 */

#pragma once

#include "BusinessLogic/Inc/ApplicationComponent.hpp"
#include "PlatformFactory.hpp"
#include "Device/Inc/RecorderVariant.hpp"
#include "Device/Inc/SourceVariant.hpp"
#include "BusinessLogic/Inc/HmiFacade.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"

#include "Device/Inc/PulseCounterSource.hpp"
#include "Device/Inc/UartSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/WiFiRecorder.hpp"
#include "Device/Inc/SdCardRecorder.hpp"
#include "Device/Inc/Display.hpp"
#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/DisplayBrightness.hpp"

#include <array>
#include <cstddef>
#include <functional>
#include <utility>
#include <variant>

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
     */
    class ApplicationFacade final : public ApplicationComponent
    {
    public:
        explicit ApplicationFacade(Driver::PlatformFactory &factory) noexcept;

        ~ApplicationFacade() = default;

        // Non-copyable and non-movable
        ApplicationFacade() = delete;
        ApplicationFacade(const ApplicationFacade &) = delete;
        ApplicationFacade(ApplicationFacade &&) = delete;
        ApplicationFacade &operator=(const ApplicationFacade &) = delete;
        ApplicationFacade &operator=(ApplicationFacade &&) = delete;

        // Lifecycle hooks (called by base class)
        [[nodiscard]] bool onInit() noexcept;
        [[nodiscard]] bool onStart() noexcept;
        [[nodiscard]] bool onStop() noexcept;
        [[nodiscard]] bool onTick() noexcept;

    private:
        static constexpr std::size_t SOURCES_COUNT{
            std::to_underlying(Device::MeasurementDeviceId::LAST_NOT_USED)};
        static constexpr std::size_t RECORDERS_COUNT{2};

        Device::PulseCounterSource pulseCounter1;
        Device::PulseCounterSource pulseCounter2;
        Device::PulseCounterSource pulseCounter3;
        Device::PulseCounterSource pulseCounter4;
        Device::UartSource uartReceiver;

        std::array<Device::SourceVariant, SOURCES_COUNT> sources;

        Device::WiFiRecorder wifiRecorder;
        Device::SdCardRecorder sdCardRecorder;
        std::array<Device::RecorderVariant, RECORDERS_COUNT> recorders;

        MeasurementCoordinator<SOURCES_COUNT, RECORDERS_COUNT> measurementCoordinator;

        Device::Display display;
        Device::DisplayBrightness brightnessRegulator;
        Device::Keyboard keyboard;
        BusinessLogic::HmiFacade hmi;
    };

} // namespace BusinessLogic
