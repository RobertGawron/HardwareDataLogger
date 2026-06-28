module;

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <span>
#include <utility>
#include <limits>

export module BusinessLogic.SlotTableScheduler;

import BusinessLogic.TickDelegate;
import BusinessLogic.TaskId;

import Driver.CycleCpu;
import Driver.CycleClock;

export namespace BusinessLogic
{
    /**
     * @brief Scheduler error / latch state.
     *
     * @details
     * This enumeration reports scheduler-level error conditions. Error reporting uses a
     * "last error wins" policy: @ref Status::error may be overwritten during execution if
     * multiple conditions occur.
     *
     * Latched flags in @ref Status (taskFailed/slotOverrun/schedulerLag) keep cumulative
     * information until clearStatus() is called, even if @ref Status::error is overwritten.
     */
    enum class Error : std::uint8_t
    {
        /// @brief No error reported.
        NONE = 0,

        /// @brief runPending() was called before start() completed successfully.
        NOT_STARTED,

        /// @brief Task call table was not fully bound when start() was called.
        REGISTRY_INCOMPLETE,

        /// @brief At least one task returned false; failure is latched.
        TASK_FAILED_LATCHED,

        /// @brief Slot runtime exceeded its configured cycle budget; overrun is latched.
        SLOT_OVERRUN_LATCHED,

        /// @brief Pending backlog exceeded maxCatchUpPerCall; lag is latched.
        SCHEDULER_LAG_LATCHED
    };

    /**
     * @brief Runtime status snapshot of the scheduler.
     *
     * @details
     * Status is updated during scheduler operation and provides:
     * - A latched error code (@ref error) following a "last error wins" policy.
     * - Latched boolean fault flags (taskFailed/slotOverrun/schedulerLag) that remain set
     *   until clearStatus() is called.
     * - Timing endpoints (lastStart/lastEnd) of the most recently executed slot. Elapsed
     *   cycles can be computed by the caller using Driver::CycleClock::elapsed().
     *
     * This structure is intended for diagnostics/logging and is safe to read from the main
     * thread context. It is not intended to be written outside of SlotTableScheduler.
     */
    struct Status final
    {
        /**
         * @brief Most recently recorded scheduler error ("last error wins").
         *
         * @details
         * This value may be overwritten during a run if multiple conditions occur.
         * Use the boolean flags (taskFailed/slotOverrun/schedulerLag) for cumulative
         * latched diagnostics.
         */
        Error error{Error::NONE};

        /**
         * @brief Latched task-failure flag.
         *
         * @details
         * Set to true when any executed task returns false. Remains true until clearStatus().
         */
        bool taskFailed{false};

        /**
         * @brief Latched slot-overrun flag.
         *
         * @details
         * Set to true when elapsed slot cycles exceed Slot::budgetCycles (when budgetCycles != 0).
         * Remains true until clearStatus().
         */
        bool slotOverrun{false};

        /**
         * @brief Latched scheduler-lag flag.
         *
         * @details
         * Set to true when pendingSlotsAtStart > maxCatchUpPerCall at the beginning of runPending().
         * Remains true until clearStatus().
         */
        bool schedulerLag{false};

        /**
         * @brief Index of the most recently executed slot.
         *
         * Range: [0, SlotsPerCycle - 1].
         */
        std::size_t lastSlot{0U};

        /**
         * @brief CPU cycle counter at start of last executed slot.
         *
         * @details
         * Read from Driver::CycleClock::now().
         */
        Driver::CycleCpu lastStart{0U};

        /**
         * @brief CPU cycle counter at end of last executed slot.
         *
         * @details
         * Read from Driver::CycleClock::now().
         */
        Driver::CycleCpu lastEnd{0U};

        /**
         * @brief Pending slot backlog observed at the beginning of runPending().
         *
         * @details
         * This is a snapshot of the atomic pending slot counter before executing any slots
         * in the current runPending() call.
         */
        std::uint32_t pendingSlotsAtStart{0U};

        /**
         * @brief Pending slot backlog observed after runPending() completes.
         *
         * @details
         * Snapshot taken after executing up to maxCatchUpPerCall slots.
         * Note: the backlog may increase concurrently due to ISR activity.
         */
        std::uint32_t backlogAfterRun{0U};
    };

    /**
     * @brief Cooperative fixed slot-table scheduler (ISR-driven).
     *
     * @tparam SlotsPerCycle   Number of slots in one scheduler cycle.
     * @tparam MaxTasksPerSlot Maximum number of tasks that can execute in a slot.
     *
     * @details
     * High-level behavior:
     * - An ISR calls notifyTimeSlotIsr() to indicate that a scheduling time slot has elapsed.
     * - The main loop calls runPending() to execute pending slots. Each executed slot runs
     *   a configured list of tasks (identified by TaskId).
     *
     * Configuration model:
     * - SlotTable defines which TaskId values run in each slot and optional per-slot cycle budgets.
     * - TaskCallTable maps each TaskId to a TickDelegate used to call the task.
     *
     * Error handling:
     * - start() validates that the TaskCallTable is complete (all delegates bound).
     * - runPending() latches diagnostic information into @ref Status:
     *   - schedulerLag when backlog exceeds maxCatchUpPerCall at the start of the call
     *   - taskFailed when any task returns false
     *   - slotOverrun when a slot exceeds its cycle budget (budgetCycles != 0)
     *
     * Error reporting policy:
     * - @ref Status::error is "last error wins" (may overwrite previous errors).
     * - Boolean flags remain latched until clearStatus().
     *
     * Lifetime:
     * - This scheduler is non-owning. SlotTable and TaskCallTable are referenced and must
     *   outlive the SlotTableScheduler instance.
     */
    template <std::size_t SlotsPerCycle, std::size_t MaxTasksPerSlot>
    class SlotTableScheduler final
    {
    public:
        /**
         * @brief Number of tasks supported by the scheduler.
         *
         * @details
         * The number is derived from TaskId::LAST_NOT_USED. The TaskCallTable must contain one
         * TickDelegate per TaskId value in [0, LAST_NOT_USED).
         */
        static constexpr std::size_t TASK_COUNT = std::to_underlying(TaskId::LAST_NOT_USED);

        /**
         * @brief Definition of one slot in the schedule.
         *
         * @details
         * Slots are typically configured at compile time and treated as immutable configuration.
         * Only the first @ref taskIdCount elements of @ref taskIds are executed.
         */
        struct Slot final
        {
            /**
             * @brief Ordered task identifiers executed in this slot.
             *
             * @details
             * The scheduler executes tasks sequentially in this order.
             */
            const std::array<TaskId, MaxTasksPerSlot> taskIds{};

            /**
             * @brief Number of valid entries in @ref taskIds.
             *
             * @details
             * Must be <= MaxTasksPerSlot.
             */
            const std::uint8_t taskIdCount{0U};

            /**
             * @brief Cycle budget for this slot.
             *
             * @details
             * If budgetCycles is zero, slot overrun checking is disabled for this slot.
             * Otherwise, slotOverrun is latched when elapsed > budgetCycles.
             */
            const Driver::CycleCpu budgetCycles{0U};
        };

        /// @brief Schedule table containing SlotsPerCycle slot definitions.
        using SlotTable = std::array<Slot, SlotsPerCycle>;

        /**
         * @brief Task call table indexed by TaskId.
         *
         * @details
         * Each entry must be bound before start() is called, otherwise start() fails with
         * Error::REGISTRY_INCOMPLETE.
         */
        using TaskCallTable = std::array<TickDelegate, TASK_COUNT>;

        /**
         * @brief Scheduler configuration.
         *
         * @details
         * All references are non-owning; referenced objects must outlive the scheduler.
         */
        struct Config final
        {
            /// @brief Immutable schedule configuration.
            const SlotTable &slotTable;

            /// @brief Immutable task invocation table (one entry per TaskId).
            const TaskCallTable &taskCallTable;

            /**
             * @brief Maximum number of slots executed per runPending() call.
             *
             * @details
             * Limits main-loop execution time. If the backlog at call entry is greater than this
             * value, schedulerLag is latched.
             */
            std::uint32_t maxCatchUpPerCall{2U};
        };

        /**
         * @brief Constructs the scheduler.
         *
         * @details
         * Construction does not start timing or validate binding. Validation is performed in start().
         *
         * @param cfg Non-owning configuration references.
         */
        explicit SlotTableScheduler(const Config &cfg) noexcept
            : slotTableRef(cfg.slotTable),
              taskCallTable(cfg.taskCallTable),
              maxCatchUpPerCall(cfg.maxCatchUpPerCall),
              slotIndex(0U),
              pendingSlots(0U),
              isStarted(false),
              status{}
        {
        }

        /**
         * @brief Starts the scheduler.
         *
         * @details
         * - Validates that every TickDelegate in the TaskCallTable is bound.
         * - Initializes the cycle counter driver.
         * - Resets slot index, pending backlog, and status diagnostics.
         *
         * @return True if the scheduler started successfully; false otherwise.
         */
        [[nodiscard]] auto start() noexcept -> bool
        {
            if (isTaskCallTableComplete())
            {
                Driver::CycleClock::init();
                slotIndex = 0U;
                pendingSlots.store(0U, std::memory_order_relaxed);
                isStarted = true;
                status = Status{};
            }
            else
            {
                status.error = Error::REGISTRY_INCOMPLETE;
                isStarted = false;
            }

            return isStarted;
        }

        /**
         * @brief ISR hook: increments the pending slot backlog by one.
         *
         * @details
         * Intended to be called from interrupt context. Uses relaxed atomic operations because
         * only the numeric value of the counter is required.
         */
        auto notifyTimeSlotIsr() noexcept -> void
        {
            pendingSlots.fetch_add(1U, std::memory_order_relaxed);
        }

        /**
         * @brief Executes pending slots up to the configured catch-up limit.
         *
         * @details
         * If called before start(), NOT_STARTED is stored in status.error and false is returned.
         *
         * In one call, at most maxCatchUpPerCall slots are executed. If the backlog at call entry
         * exceeds maxCatchUpPerCall, schedulerLag is latched.
         *
         * @return True if the scheduler was started and did not begin the call with lag;
         *         false otherwise (NOT_STARTED or lag at entry).
         */
        [[nodiscard]] auto runPending() noexcept -> bool
        {
            bool result = true;

            if (!isStarted)
            {
                status.error = Error::NOT_STARTED;
                result = false;
            }
            else
            {
                status.pendingSlotsAtStart = pendingSlots.load(std::memory_order_relaxed);

                if (status.pendingSlotsAtStart > maxCatchUpPerCall)
                {
                    status.schedulerLag = true;
                    status.error = Error::SCHEDULER_LAG_LATCHED;
                }

                const std::uint32_t toRun =
                    (status.pendingSlotsAtStart < maxCatchUpPerCall)
                        ? status.pendingSlotsAtStart
                        : maxCatchUpPerCall;

                for (std::uint32_t i = 0U; i < toRun; ++i)
                {
                    const Slot &slot = slotTableRef[slotIndex];

                    std::span<const TaskId> taskIds{slot.taskIds};
                    taskIds = taskIds.first(slot.taskIdCount);

                    status.lastSlot = slotIndex;
                    status.lastStart = Driver::CycleClock::now();

                    for (TaskId taskId : taskIds)
                    {
                        const std::size_t taskIdx = std::to_underlying(taskId);

                        if (taskCallTable[taskIdx]() == false)
                        {
                            status.taskFailed = true;
                            status.error = Error::TASK_FAILED_LATCHED;
                        }
                    }

                    status.lastEnd = Driver::CycleClock::now();

                    const Driver::CycleCpu elapsed =
                        Driver::CycleClock::elapsed(status.lastStart, status.lastEnd);

                    if ((slot.budgetCycles != 0U) && (elapsed > slot.budgetCycles))
                    {
                        status.slotOverrun = true;
                        status.error = Error::SLOT_OVERRUN_LATCHED;
                    }

                    // Circular increment.
                    (++slotIndex) %= SlotsPerCycle;
                }

                status.backlogAfterRun = pendingSlots.load(std::memory_order_relaxed);

                if (status.pendingSlotsAtStart > maxCatchUpPerCall)
                {
                    result = false;
                }
            }

            return result;
        }

        /**
         * @brief Returns a const reference to the current scheduler status.
         *
         * @details
         * The reference remains valid for the lifetime of the scheduler object.
         * The returned status may change after subsequent calls to start(), runPending(), or clearStatus().
         */
        [[nodiscard]] auto getStatus() const noexcept -> const Status &
        {
            return status;
        }

        /**
         * @brief Clears latched status flags and error code.
         *
         * @details
         * Does not modify the scheduler started state and does not affect the pending slot backlog.
         */
        auto clearStatus() noexcept -> void
        {
            status = Status{};
        }

    private:
        /**
         * @brief Validates that the TaskCallTable contains only bound delegates.
         *
         * @details
         * This is a runtime check because binding depends on runtime object addresses.
         * It is called by start() to prevent executing unbound delegates.
         *
         * @return True if every delegate is bound; false otherwise.
         */
        [[nodiscard]] auto isTaskCallTableComplete() const noexcept -> bool
        {
            bool complete = true;

            for (const TickDelegate &entry : taskCallTable)
            {
                if (!entry.isBound())
                {
                    complete = false;
                }
            }

            return complete;
        }

        /// @brief Immutable reference to the configured slot schedule.
        const SlotTable &slotTableRef;

        /// @brief Immutable reference to the task call table indexed by TaskId.
        const TaskCallTable &taskCallTable;

        /// @brief Catch-up limit applied in runPending().
        std::uint32_t maxCatchUpPerCall;

        /// @brief Index of the next slot to execute.
        std::size_t slotIndex;

        /// @brief Pending slot backlog (incremented by ISR).
        std::atomic<std::uint32_t> pendingSlots;

        /// @brief True once start() has completed successfully.
        bool isStarted;

        /// @brief Latched diagnostics and timing endpoints.
        Status status;

        static_assert(SlotsPerCycle > 0U,
                      "SlotsPerCycle must be greater than zero (required for slot indexing and modulo wrap).");

        static_assert(MaxTasksPerSlot > 0U,
                      "MaxTasksPerSlot must be greater than zero (each slot must be able to hold at least one TaskId).");

        // Slot::taskIdCount is uint8_t, ensure the configured capacity is representable.
        static_assert(MaxTasksPerSlot <= static_cast<std::size_t>(std::numeric_limits<std::uint8_t>::max()),
                      "MaxTasksPerSlot must fit into std::uint8_t because Slot::taskIdCount uses uint8_t.");

        // Task table sanity.
        static_assert(TASK_COUNT > 0U,
                      "TaskId::LAST_NOT_USED must be greater than zero (scheduler requires at least one task).");

        // These asserts defend the use of std::to_underlying(TaskId) as an array index.
        static_assert(std::to_underlying(TaskId::LAST_NOT_USED) == TASK_COUNT,
                      "TASK_COUNT must match TaskId::LAST_NOT_USED (TaskCallTable indexing relies on this).");

        static_assert(std::to_underlying(TaskId{0}) == 0U,
                      "TaskId must be zero-based for array indexing (expected first task id to be 0).");

        // Representation/ABI expectations.
        static_assert(std::is_nothrow_invocable_r_v<bool, decltype(&TickDelegate::operator()), const TickDelegate &>,
                      "TickDelegate invocation must be noexcept and return bool (scheduler assumes it can call tasks without exceptions).");

        // Deterministic storage expectations.
        static_assert(std::is_standard_layout_v<Status>,
                      "Status must have standard layout for predictable representation in aembedded builds.");

        static_assert(std::is_trivially_copyable_v<Status>,
                      "Status should be trivially copyable to allow safe snapshotting/logging without hidden side effects.");
    };
} // namespace BusinessLogic