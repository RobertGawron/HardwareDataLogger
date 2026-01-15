module;

#include <array>
#include <cstdint>
#include <cstddef>

module Driver.PulseCounterDriver;

import Driver.PulseCounterId;

namespace
{
    using CounterArray = std::array<
        Driver::PulseCounterMeasurementSize,
        Driver::PulseCounterDriver::PULSE_COUNTER_AMOUNT>;

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