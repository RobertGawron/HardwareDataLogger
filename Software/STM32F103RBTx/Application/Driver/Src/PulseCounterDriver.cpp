#include "Driver/Interfaces/IPulseCounterDriver.hpp"
#include "Driver/Inc/PulseCounterDriver.hpp"
#include "Driver/Inc/PulseCounterIdentifier.hpp"

#include <cstdint>
#include <array>

using PulseCounterArray = std::array<
    Driver::PulseCounterDriver::CounterSizeType,
    Driver::PulseCounterDriver::PULSE_COUNTER_AMOUNT>;

static PulseCounterArray pulseCounters = {0};

// Expose the array pointer for C compatibility
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
}

namespace Driver
{
    PulseCounterDriver::PulseCounterDriver(PulseCounterIdentifier id) : value(pulseCounters[(int)id])
    {
    }

    PulseCounterDriver::~PulseCounterDriver()
    {
        clearMeasurement();
    }

    bool PulseCounterDriver::onInitialize()
    {
        pulseCounters.fill(0u);
        return true;
    }

    bool PulseCounterDriver::onStart()
    {
        pulseCounters.fill(0u);
        return true;
    }

    bool PulseCounterDriver::onStop()
    {
        return true;
    }

    bool PulseCounterDriver::onReset()
    {
        return true;
    }

    IPulseCounterDriver::CounterSizeType PulseCounterDriver::getMeasurement()
    {
        return value;
    }

    void PulseCounterDriver::clearMeasurement()
    {
        value = 0;
    }

}
