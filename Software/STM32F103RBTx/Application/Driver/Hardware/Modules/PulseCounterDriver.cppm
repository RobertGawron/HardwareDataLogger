module;

#include <cstdint>
#include <utility>

export module Driver.PulseCounterDriver;

import Driver.DriverComponent;
import Driver.PulseCounterDriverConcept;
import Driver.PulseCounterId;
import Driver.PulseCount;

export namespace Driver
{
    /**
     * @class PulseCounterDriver
     * @brief Hardware abstraction layer for external pulse counting via GPIO interrupts.
     *
     * This driver provides access to hardware pulse counters connected to BNC connectors.
     * Each instance references a shared counter that is incremented atomically from
     * interrupt context (EXTI handler).
     *
     * @note Thread-safe: Counter increments are atomic (single instruction on Cortex-M).
     * @note Debouncing is done in hardware.
     * @note The counter is never reset automatically - client code must call clear().
     * @note Multiple instances can reference the same counter if needed.
     *
     * @warning Reading the counter on platforms without atomic 32-bit loads may require
     *          disabling interrupts briefly to ensure consistency.
     */
    class PulseCounterDriver final : public DriverComponent
    {
    public:
        /**
         * @brief Constructs a pulse counter driver for the specified device.
         * @param deviceId Identifier of the pulse counter (BNC connector).
         */
        explicit PulseCounterDriver(PulseCounterId deviceId) noexcept;

        ~PulseCounterDriver() = default;

        PulseCounterDriver() = delete;
        PulseCounterDriver(const PulseCounterDriver &) = delete;
        PulseCounterDriver &operator=(const PulseCounterDriver &) = delete;
        PulseCounterDriver(PulseCounterDriver &&) = delete;
        PulseCounterDriver &operator=(PulseCounterDriver &&) = delete;

        /**
         * @brief Reads the current pulse count.
         * @return Current accumulated pulse count since last clear().
         * @note This is a non-blocking read of a shared volatile counter.
         * @note On STM32F1 (Cortex-M3), 32-bit reads are atomic.
         */
        [[nodiscard]] auto read() const noexcept -> PulseCount;

        /**
         * @brief Resets the pulse counter to zero.
         * @note This does not disable interrupts - new pulses may arrive immediately.
         */
        auto clear() noexcept -> void;

        /**
         * @brief Initializes the pulse counter driver.
         * @return Always returns true (no initialization required, API constraints).
         * @note Hardware GPIO configuration is performed externally (CubeMX).
         */
        [[nodiscard]] constexpr bool onInit() noexcept { return true; }

        /**
         * @brief Starts pulse counting by clearing the counter.
         * @return Always returns true (API constraints).
         * @note Interrupts are already enabled - this just resets the count.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Stops pulse counting by clearing the counter.
         * @return Always returns true (API constraints).
         * @note Does not disable GPIO interrupts - pulses continue to be counted.
         *       This method only resets the counter value to prepare for next session.
         */
        [[nodiscard]] constexpr bool onStop() noexcept { return true; }

    private:
        /**
         * @brief Reference to the shared hardware counter for this device.
         * @note Modified from ISR context - ensure atomic access patterns.
         */
        PulseCount &counter;
    };

    static_assert(Concepts::PulseCounterDriverConcept<PulseCounterDriver>,
                  "PulseCounterDriver must satisfy the concept requirements");

} // namespace Driver