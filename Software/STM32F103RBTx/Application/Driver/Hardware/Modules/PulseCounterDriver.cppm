module;

#include <cstdint>

export module Driver.PulseCounterDriver;

import Driver.DriverComponent;
import Driver.PulseCounterDriverConcept;
import Driver.PulseCounterId;
import Driver.PulseCounterMeasurementSize;

extern "C"
{
    /**
     * @brief Increments pulse counter from interrupt context
     * @param counterId Counter identifier to increment
     * @note Called by hardware interrupt handler - must be fast and noexcept
     */
    void incrementPulseCounter(std::uint8_t counterId) noexcept;
}

export namespace Driver
{
    /**
     * @class PulseCounterDriver
     * @brief Hardware abstraction for pulse counting with zero-overhead interface
     */
    class PulseCounterDriver final : public DriverComponent
    {
    public:
        static constexpr std::uint8_t PULSE_COUNTER_AMOUNT = 4U;

        explicit PulseCounterDriver(PulseCounterId deviceIdentifier) noexcept;

        ~PulseCounterDriver() = default;

        PulseCounterDriver() = delete;
        PulseCounterDriver(const PulseCounterDriver &) = delete;
        PulseCounterDriver &operator=(const PulseCounterDriver &) = delete;
        PulseCounterDriver(PulseCounterDriver &&) = delete;
        PulseCounterDriver &operator=(PulseCounterDriver &&) = delete;

        [[nodiscard]] auto getMeasurement() noexcept -> PulseCounterMeasurementSize;
        void clearMeasurement() noexcept;

        [[nodiscard]] bool onInit();
        [[nodiscard]] bool onStart();
        [[nodiscard]] bool onStop();

    private:
        PulseCounterMeasurementSize &value;
    };

    static_assert(Driver::Concepts::PulseCounterDriverConcept<PulseCounterDriver>,
                  "PulseCounterDriver must satisfy the concept requirements");

} // namespace Driver