/**
 * @file ApplicationFacade.hpp
 * @brief Defines the ApplicationFacade class responsible for orchestrating application component initialization.
 */

#ifndef APPLICATION_FACADE_HPP
#define APPLICATION_FACADE_HPP

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

#include <array>
#include <cstddef>
#include <functional>
#include <utility>

namespace Device
{
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
     */
    class ApplicationFacade final : public IApplicationFacade
    {
    public:
        explicit ApplicationFacade(IPlatformFactory &factory) noexcept;

        ~ApplicationFacade() override = default;

        // Non-copyable and non-movable
        ApplicationFacade() = delete;
        ApplicationFacade(const ApplicationFacade &) = delete;
        ApplicationFacade(ApplicationFacade &&) = delete;
        ApplicationFacade &operator=(const ApplicationFacade &) = delete;
        ApplicationFacade &operator=(ApplicationFacade &&) = delete;

        [[nodiscard]] bool initialize() noexcept override;
        [[nodiscard]] bool start() noexcept override;
        [[nodiscard]] bool stop() noexcept override;
        [[nodiscard]] bool tick() noexcept override;

    private:
        static constexpr std::size_t SOURCES_COUNT{
            std::to_underlying(Device::MeasurementDeviceId::LAST_NOT_USED)};
        static constexpr std::size_t RECORDERS_COUNT{2};

        Device::PulseCounterMeasurementSource pulseCounter1;
        Device::PulseCounterMeasurementSource pulseCounter2;
        Device::PulseCounterMeasurementSource pulseCounter3;
        Device::PulseCounterMeasurementSource pulseCounter4;
        Device::UartMeasurementSource uartReceiver;

        std::array<std::reference_wrapper<Device::IMeasurementSource>, SOURCES_COUNT> sources;

        Device::WiFiMeasurementRecorder wifiRecorder;
        Device::SdCardMeasurementRecorder sdCardRecorder;
        std::array<std::reference_wrapper<Device::IMeasurementRecorder>, RECORDERS_COUNT> recorders;

        MeasurementCoordinator<SOURCES_COUNT, RECORDERS_COUNT> measurementCoordinator;

        Device::Display display;
        Device::DisplayBrightnessRegulator brightnessRegulator;
        Device::Keyboard keyboard;
        BusinessLogic::HmiFacade hmi;
    };

} // namespace BusinessLogic

#endif // APPLICATION_FACADE_HPP