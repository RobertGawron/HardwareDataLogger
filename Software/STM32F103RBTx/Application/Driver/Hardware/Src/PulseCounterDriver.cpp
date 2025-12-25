#include "Driver/Interface/IPulseCounterDriver.hpp"
#include "Driver/Hardware/Inc/PulseCounterDriver.hpp"
#include "Driver/Interface/PulseCounterIdentifier.hpp"

#include <cstdint>
#include <cstddef> // For std::size_t
#include <array>

namespace
{
    using PulseCounterArray = std::array<
        Driver::PulseCounterDriver::CounterSizeType,
        Driver::PulseCounterDriver::PULSE_COUNTER_AMOUNT>;

    PulseCounterArray pulseCounters = {0};
}

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
    PulseCounterDriver::PulseCounterDriver(PulseCounterIdentifier deviceIdentifier)
        : value(pulseCounters[static_cast<std::size_t>(deviceIdentifier)])
    {
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
        clearMeasurement();
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
