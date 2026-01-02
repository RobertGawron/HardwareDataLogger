/**
 * @file PulseCounterDriver.cpp
 * @brief Implementation of pulse counter driver with C++23 features
 */

#include "Driver/Hardware/Inc/PulseCounterDriver.hpp"
#include "PulseCounterDriver.hpp"
#include "Driver/Interface/PulseCounterId.hpp"

#include <array>
#include <cstdint>
#include <cstddef>

namespace
{
    // Modern type alias with clearer intent
    using CounterArray = std::array<
        Driver::PulseCounterMeasurementSize,
        Driver::PulseCounterDriver::PULSE_COUNTER_AMOUNT>;

    // Zero-initialized at compile time
    constinit CounterArray pulseCounters{};
}

extern "C"
{
    void incrementPulseCounter(std::uint8_t counterId) noexcept
    {
        if (counterId < pulseCounters.size()) [[likely]]
        {
            ++pulseCounters[counterId];
        }
    }
}

namespace Driver
{
    PulseCounterDriver::PulseCounterDriver(PulseCounterId deviceIdentifier) noexcept
        : value(pulseCounters[static_cast<std::size_t>(deviceIdentifier)])
    {
    }

    bool PulseCounterDriver::onInit() noexcept
    {
        pulseCounters.fill(0U);
        return true;
    }

    bool PulseCounterDriver::onStart() noexcept
    {
        pulseCounters.fill(0U);
        return true;
    }

    bool PulseCounterDriver::onStop() noexcept
    {
        clearMeasurement();
        return true;
    }

    auto PulseCounterDriver::getMeasurement() noexcept -> PulseCounterMeasurementSize
    {
        return value;
    }

    void PulseCounterDriver::clearMeasurement() noexcept
    {
        value = 0U;
    }

} // namespace Driver