module;

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <utility>

export module BusinessLogic.MeasurementSubsystem;

import BusinessLogic.ApplicationComponent;
import BusinessLogic.MeasurementCoordinator;
import BusinessLogic.EveryNCalls;

import Device;
import Driver.PlatformFactory;

export namespace BusinessLogic
{
    /**
     * @brief Subsystem responsible for managing measurement sources, recorders,
     * and the measurement coordinator lifecycle.
     */
    class MeasurementSubsystem final : public ApplicationComponent
    {
    public:
        /**
         * @brief Constructs the subsystem using platform-provided drivers.
         */
        explicit MeasurementSubsystem(Driver::PlatformFactory &factory) noexcept;

        ~MeasurementSubsystem() = default;

        MeasurementSubsystem() = delete;
        MeasurementSubsystem(const MeasurementSubsystem &) = delete;
        MeasurementSubsystem(MeasurementSubsystem &&) = delete;
        MeasurementSubsystem &operator=(const MeasurementSubsystem &) = delete;
        MeasurementSubsystem &operator=(MeasurementSubsystem &&) = delete;

        /**
         * @brief Initializes the measurement coordinator (and its sources/recorders).
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Starts the measurement coordinator.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Stops the measurement coordinator.
         */
        [[nodiscard]] auto onStop() noexcept -> bool;

        /**
         * @brief Executes one tick of the throttled measurement coordinator.
         * @note Satisfies TickableConcept via ApplicationComponent::tick() -> onTick().
         */
        [[nodiscard]] auto onTick() noexcept -> bool;

    private:
        /// Number of recorders connected to the measurement coordinator.
        static constexpr std::size_t RECORDERS_COUNT{2U};

        /// Number of sources connected to the measurement coordinator.
        static constexpr std::size_t SOURCES_COUNT{
            std::to_underlying(Device::MeasurementDeviceId::LAST_NOT_USED)};

        // Measurement sources
        Device::PulseCounterSource pulseCounter1;
        Device::PulseCounterSource pulseCounter2;
        Device::PulseCounterSource pulseCounter3;
        Device::PulseCounterSource pulseCounter4;
        Device::UartSource uartReceiver;

        using SourceArray = std::array<Device::SourceVariant, SOURCES_COUNT>;
        SourceArray sources;

        // Measurement recorders
        Device::WiFiRecorder wifiRecorder;
        Device::SdCardRecorder sdCardRecorder;

        using RecorderArray = std::array<Device::RecorderVariant, RECORDERS_COUNT>;
        RecorderArray recorders;

        using MeasurementCoordinatorType =
            BusinessLogic::MeasurementCoordinator<SourceArray, RecorderArray>;

        MeasurementCoordinatorType measurement;

#warning dont hardcode, made methods for TIM2 data move to driver
        static constexpr std::uint32_t MEASUREMENT_EVERY_N_CALLS = 12'000U;

        using MeasurementEveryMinute =
            BusinessLogic::EveryNCalls<MeasurementCoordinatorType, MEASUREMENT_EVERY_N_CALLS>;

        MeasurementEveryMinute measurementEveryMinute;
    };

} // namespace BusinessLogic