module;

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <utility>

export module BusinessLogic.SlotTableScheduler;

import BusinessLogic.TickableConcept;
import BusinessLogic.TickDelegate;
import Driver.CycleCpu;
import Driver.CycleClock;

export namespace BusinessLogic
{
    enum class Error : std::uint8_t
    {
        NONE = 0,
        NOT_STARTED,
        REGISTRY_INCOMPLETE,
        TASK_FAILED_LATCHED,
        SLOT_OVERRUN_LATCHED,
        SCHEDULER_LAG_LATCHED
    };

    struct Status final
    {
        Error error{Error::NONE};

        bool taskFailed{false};
        bool slotOverrun{false};
        bool schedulerLag{false};

        std::size_t lastSlot{0U};
        Driver::CycleCpu lastStart{0U};
        Driver::CycleCpu lastEnd{0U};
        Driver::CycleCpu lastElapsed{0U};

        std::uint32_t pendingAtStart{0U};
        std::uint32_t backlogAfterRun{0U};
    };

    template <std::size_t SlotsPerCycle, std::size_t MaxTasksPerSlot>
    class SlotTableScheduler final
    {
    public:
        enum class TaskId : std::uint8_t
        {
            MEASUREMENT = 0,
            HMI = 1,
            LAST_NOT_USED
        };

        static constexpr std::size_t taskCount = std::to_underlying(TaskId::LAST_NOT_USED);

        struct SlotDef final
        {
            std::array<TaskId, MaxTasksPerSlot> taskIds{};
            std::uint8_t taskIdCount{0U};
            Driver::CycleCpu budgetCycles{0U}; // 0 disables overrun check
        };

        using SlotTable = std::array<SlotDef, SlotsPerCycle>;
        using Registry = std::array<TickDelegate, taskCount>;

        struct Config final
        {
            const SlotTable &slotTable;
            std::uint32_t maxCatchUpPerCall{2U};
        };

        explicit SlotTableScheduler(const Config &cfg) noexcept
            : slotTableRef(cfg.slotTable), registry{}, maxCatchUpPerCall(cfg.maxCatchUpPerCall), slotIndex(0U), pendingSlots(0U), started(false), statusValue{}
        {
        }

        template <TickableConcept T>
        auto bindTask(TaskId id, T &obj) noexcept -> bool
        {
            bool result = false;

            const std::size_t idx = std::to_underlying(id);
            if (idx < registry.size())
            {
                registry[idx] = TickDelegate(obj);
                result = true;
            }
            else
            {
                statusValue.error = Error::REGISTRY_INCOMPLETE;
                result = false;
            }

            return result;
        }

        auto start() noexcept -> bool
        {
            bool result = false;

            if (isRegistryComplete())
            {
                Driver::CycleClock::init();
                slotIndex = 0U;
                pendingSlots.store(0U, std::memory_order_relaxed);
                started = true;
                statusValue = Status{};
                result = true;
            }
            else
            {
                statusValue.error = Error::REGISTRY_INCOMPLETE;
                started = false;
                result = false;
            }

            return result;
        }

        auto notifyTimeSlotIsr() noexcept -> void
        {
            pendingSlots.fetch_add(1U, std::memory_order_relaxed);
        }

        auto runPending() noexcept -> bool
        {
            bool result = true;

            if (!started)
            {
                statusValue.error = Error::NOT_STARTED;
                result = false;
            }
            else
            {
                const std::uint32_t pendingStart = pendingSlots.load(std::memory_order_relaxed);
                statusValue.pendingAtStart = pendingStart;

                if (pendingStart > maxCatchUpPerCall)
                {
                    statusValue.schedulerLag = true;
                    statusValue.error = Error::SCHEDULER_LAG_LATCHED;
                }

                const std::uint32_t toRun =
                    (pendingStart < maxCatchUpPerCall) ? pendingStart : maxCatchUpPerCall;

                for (std::uint32_t i = 0U; i < toRun; ++i)
                {
                    // Consume one pending slot if available.
                    if (pendingSlots.load(std::memory_order_relaxed) > 0U)
                    {
                        (void)pendingSlots.fetch_sub(1U, std::memory_order_relaxed);
                    }

                    executeOneSlot();

                    if (statusValue.taskFailed || statusValue.slotOverrun)
                    {
                        result = false;
                    }
                }

                statusValue.backlogAfterRun = pendingSlots.load(std::memory_order_relaxed);

                if (pendingStart > maxCatchUpPerCall)
                {
                    result = false;
                }
            }

            return result;
        }

        [[nodiscard]] auto status() const noexcept -> Status
        {
            Status result = statusValue;
            return result;
        }

        auto clearStatus() noexcept -> void
        {
            statusValue = Status{};
        }

    private:
        [[nodiscard]] auto isRegistryComplete() const noexcept -> bool
        {
            bool complete = true;

            for (const auto &entry : registry)
            {
                if (!entry.isBound())
                {
                    complete = false;
                }
            }

            return complete;
        }

        auto executeOneSlot() noexcept -> void
        {
            const auto &slot = slotTableRef[slotIndex];

            statusValue.lastSlot = slotIndex;

            const Driver::CycleCpu startCycleCpu = Driver::CycleClock::now();
            statusValue.lastStart = startCycleCpu;

            bool allOk = true;

            for (std::uint8_t i = 0U; i < slot.taskIdCount; ++i)
            {
                const std::size_t taskIdx = std::to_underlying(slot.taskIds[i]);

                const bool ok = registry[taskIdx]();
                if (!ok)
                {
                    allOk = false;
                }
            }

            const Driver::CycleCpu endCycleCpu = Driver::CycleClock::now();
            statusValue.lastEnd = endCycleCpu;

            const Driver::CycleCpu elapsed = Driver::CycleClock::elapsed(startCycleCpu, endCycleCpu);
            statusValue.lastElapsed = elapsed;

            if (!allOk)
            {
                statusValue.taskFailed = true;
                statusValue.error = Error::TASK_FAILED_LATCHED;
            }

            if ((slot.budgetCycles != 0U) && (elapsed > slot.budgetCycles))
            {
                statusValue.slotOverrun = true;
                statusValue.error = Error::SLOT_OVERRUN_LATCHED;
            }

            ++slotIndex;
            if (slotIndex >= SlotsPerCycle)
            {
                slotIndex = 0U;
            }
        }

        const SlotTable &slotTableRef;
        Registry registry;
        std::uint32_t maxCatchUpPerCall;

        std::size_t slotIndex;
        std::atomic<std::uint32_t> pendingSlots;

        bool started;
        Status statusValue;
    };
}