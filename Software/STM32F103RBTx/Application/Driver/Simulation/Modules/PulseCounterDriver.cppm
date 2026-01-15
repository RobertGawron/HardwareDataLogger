module;

#include <cstdint>

export module Driver.PulseCounterDriver;

import Driver.DriverComponent;
import Driver.PulseCounterDriverConcept;
import Driver.PulseCounterId;
import Driver.PulseCounterMeasurementSize;

export extern "C"
{
    void incrementPulseCounter(std::uint8_t counterId);
    void setPulseCounter(std::uint8_t counterId, std::uint32_t value);
}

export namespace Driver
{
    class PulseCounterDriver final : public DriverComponent
    {
    public:
        static constexpr std::uint8_t PULSE_COUNTER_AMOUNT = 4U;

        explicit PulseCounterDriver(PulseCounterId deviceId) noexcept;

        PulseCounterDriver() = delete;
        ~PulseCounterDriver() = default;

        // Non-copyable and non-movable
        PulseCounterDriver(const PulseCounterDriver &) = delete;
        PulseCounterDriver(PulseCounterDriver &&) = delete;
        PulseCounterDriver &operator=(const PulseCounterDriver &) = delete;
        PulseCounterDriver &operator=(PulseCounterDriver &&) = delete;

        // Public interface
        [[nodiscard]] PulseCounterMeasurementSize getMeasurement() noexcept;
        void clearMeasurement() noexcept;

        // Lifecycle methods
        [[nodiscard]] bool onInit() noexcept { return true; }
        [[nodiscard]] bool onStart() noexcept { return true; }
        [[nodiscard]] bool onStop() noexcept { return true; }

    private:
        PulseCounterId deviceId;
    };

    static_assert(Driver::Concepts::PulseCounterDriverConcept<PulseCounterDriver>,
                  "PulseCounterDriver must satisfy the concept requirements");
}