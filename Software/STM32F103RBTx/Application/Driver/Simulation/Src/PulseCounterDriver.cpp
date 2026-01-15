// PulseCounterDriver.cpp
module;

#include <cstdint>
#include <array>

module Driver.PulseCounterDriver;

namespace
{
    std::array<Driver::PulseCounterMeasurementSize,
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

    PulseCounterMeasurementSize PulseCounterDriver::getMeasurement() noexcept
    {
        const std::uint8_t index = static_cast<std::uint8_t>(deviceId);
        return pulseCounters[index];
    }

    void PulseCounterDriver::clearMeasurement() noexcept
    {
    }
}