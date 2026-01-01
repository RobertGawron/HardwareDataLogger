#include "PulseCounterDriverStub.hpp"
#include "Driver/Interface/PulseCounterId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

#include <cstdint>
#include <array>

namespace
{
    std::array<Driver::PulseCounterDriverStub::CounterSizeType,
               Driver::PulseCounterDriverStub::PULSE_COUNTER_AMOUNT>
        pulseCounters = {0};
}

extern "C"
{

    // C-compatible function to increment a specific counter
    void incrementPulseCounter(std::uint8_t counterId)
    {
        if (counterId < Driver::PulseCounterDriverStub::PULSE_COUNTER_AMOUNT)
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
    PulseCounterDriverStub::PulseCounterDriverStub(PulseCounterId id)
        : id(id)
    {
    }

    bool PulseCounterDriverStub::onInitialize()
    {
        return true;
    }

    bool PulseCounterDriverStub::onStart()
    {
        return true;
    }

    bool PulseCounterDriverStub::onStop()
    {
        return true;
    }

    bool PulseCounterDriverStub::onReset()
    {
        return true;
    }

    IPulseCounterDriver::CounterSizeType PulseCounterDriverStub::getMeasurement()
    {
        const std::uint8_t index = static_cast<std::uint8_t>(id);
        return pulseCounters[index];
    }

    void PulseCounterDriverStub::clearMeasurement()
    {
    }

}
