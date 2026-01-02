/**
 * @file PulseCounterDriver.hpp
 * @brief Modern C++23 pulse counter driver for embedded systems
 */

#ifndef PulseCounterDriver_h
#define PulseCounterDriver_h

#include "Driver/Interface/PulseCounterDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/PulseCounterId.hpp"
#include "Driver/Interface/PulseCounterMeasurementSize.hpp"

#include <cstdint>

extern "C"
{
    /**
     * @brief Increments pulse counter from interrupt context
     * @param counterId Counter identifier to increment
     * @note Called by hardware interrupt handler - must be fast and noexcept
     */
    void incrementPulseCounter(std::uint8_t counterId) noexcept;
}

namespace Driver
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

#endif // PulseCounterDriver_h