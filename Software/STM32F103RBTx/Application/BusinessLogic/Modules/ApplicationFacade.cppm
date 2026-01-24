/**
 * @file ApplicationFacade.cppm
 * @brief Top-level application component and scheduler owner.
 */
module;

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <utility>

export module BusinessLogic.ApplicationFacade;

import BusinessLogic.ApplicationComponent;
import BusinessLogic.MeasurementCoordinator;

import BusinessLogic.SlotTableScheduler;
import BusinessLogic.TaskId;

import Device;

import Driver.PlatformFactory;
import Driver.CycleBudget;

export namespace BusinessLogic
{
    /**
     * @brief Top-level coordinator for application subsystems.
     *
     * Owns all long-lived sources/recorders and the slot-table scheduler configuration
     * that drives periodic execution.
     */
    class ApplicationFacade final : public ApplicationComponent
    {
    public:
        /**
         * @brief Constructs the application using platform-provided drivers.
         * @param factory Driver factory providing initialized driver instances.
         */
        explicit ApplicationFacade(Driver::PlatformFactory &factory) noexcept;

        ~ApplicationFacade() = default;

        ApplicationFacade() = delete;
        ApplicationFacade(const ApplicationFacade &) = delete;
        ApplicationFacade(ApplicationFacade &&) = delete;
        ApplicationFacade &operator=(const ApplicationFacade &) = delete;
        ApplicationFacade &operator=(ApplicationFacade &&) = delete;

        /**
         * @brief Initializes all owned subsystems.
         * @return true on success; false if any subsystem initialization fails.
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Starts all owned subsystems.
         * @return true on success; false if any subsystem start fails.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Stops all owned subsystems.
         * @return true on success; false if any subsystem stop fails.
         */
        [[nodiscard]] auto onStop() noexcept -> bool;

        /**
         * @brief Runs pending scheduler slots from the main loop.
         * @return true if no scheduler error is detected during this call; false otherwise.
         */
        [[nodiscard]] auto onTick() noexcept -> bool;

        /**
         * @brief Signals one scheduler time slot.
         *
         * Intended to be called from a periodic timer interrupt or HAL callback.
         */
        auto onTimeSlot() noexcept -> void;

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

        std::array<Device::SourceVariant, SOURCES_COUNT> sources;

        // Measurement recorders
        Device::WiFiRecorder wifiRecorder;
        Device::SdCardRecorder sdCardRecorder;

        std::array<Device::RecorderVariant, RECORDERS_COUNT> recorders;

        /// Measurement routing and aggregation.
        MeasurementCoordinator<SOURCES_COUNT, RECORDERS_COUNT> measurement;

        // UI devices
        Device::Display display;
        Device::DisplayBrightness brightness;
        Device::Keyboard keyboard;

        /// Scheduler configuration.
        static constexpr std::size_t SLOTS_PER_CYCLE{4U};
        static constexpr std::size_t MAX_TASKS_PERSLOT{2U};
        static_assert(MAX_TASKS_PERSLOT > 0U, "MAX_TASKS_PERSLOT must be greater than 0.");

        using Scheduler = BusinessLogic::SlotTableScheduler<SLOTS_PER_CYCLE, MAX_TASKS_PERSLOT>;

        /// Slot schedule defining per-slot task order and budget.
        static constexpr std::array<Scheduler::Slot, SLOTS_PER_CYCLE> slotTable = {{
            Scheduler::Slot{.taskIds{TaskId::MEASUREMENT, TaskId::KEYBOARD},
                            .taskIdCount = 2U,
                            .budgetCycles = Driver::CycleBudget::fromUs(72'000'000U, 700U)},
            Scheduler::Slot{.taskIds{TaskId::MEASUREMENT},
                            .taskIdCount = 1U,
                            .budgetCycles = Driver::CycleBudget::fromUs(72'000'000U, 500U)},
            Scheduler::Slot{.taskIds{TaskId::MEASUREMENT, TaskId::KEYBOARD},
                            .taskIdCount = 2U,
                            .budgetCycles = Driver::CycleBudget::fromUs(72'000'000U, 700U)},
            Scheduler::Slot{.taskIds{TaskId::MEASUREMENT},
                            .taskIdCount = 1U,
                            .budgetCycles = Driver::CycleBudget::fromUs(72'000'000U, 500U)},
        }};

        /// Task dispatch table indexed by TaskId.
        Scheduler::TaskCallTable taskCallTable;

        /// Slot-table scheduler instance.
        Scheduler scheduler;

        /**
         * @brief Validates slotTable at compile time.
         * @return true if slotTable is internally consistent.
         */
        static consteval auto validateSlotTable() -> bool
        {
            bool ok = true;

            for (const auto &slot : slotTable)
            {
                ok = ok && (slot.taskIdCount <= MAX_TASKS_PERSLOT);

                for (std::uint8_t i = 0U; i < slot.taskIdCount; ++i)
                {
                    const auto id = std::to_underlying(slot.taskIds[i]);
                    ok = ok && (id < std::to_underlying(TaskId::LAST_NOT_USED));
                }
            }

            return ok;
        }
    };

} // namespace BusinessLogic