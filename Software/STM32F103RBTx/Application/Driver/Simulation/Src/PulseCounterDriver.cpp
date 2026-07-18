module;

#include <cstdint>
#include <array>

module Driver.PulseCounterDriver;

import Driver.PulseCounterId;

namespace
{
    std::array<Driver::PulseCount,
               Driver::PulseCounterDriver::PULSE_COUNTER_AMOUNT>
        pulseCounters = {0};
}

extern "C"
{
    // C-compatible function to increment a specific counter
    void incrementPulseCounter(std::uint8_t counterId)
    {
        if (counterId < Driver::PulseCounterDriver::PULSE_COUNTER_AMOUNT)
        {
            pulseCounters[counterId]++;
        }
    }

    void setPulseCounter(std::uint8_t counterId, std::uint32_t value)
    {
        pulseCounters[counterId] = value;
    }
}

namespace Driver
{
    PulseCounterDriver::PulseCounterDriver(PulseCounterId _deviceId) noexcept
        : deviceId(_deviceId)
    {
    }

    auto PulseCounterDriver::read() noexcept -> PulseCount
    {
        const std::uint8_t index = static_cast<std::uint8_t>(deviceId);
        return pulseCounters[index];
    }

    auto PulseCounterDriver::clear() noexcept -> void
    {
    }
}