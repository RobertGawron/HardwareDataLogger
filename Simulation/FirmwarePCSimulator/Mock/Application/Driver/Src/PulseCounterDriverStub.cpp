#include "PulseCounterDriverStub.hpp"

#include <cstdint>
#include <array>

#include <stdio.h>

// Declare a std::array to store pulse counts
static std::array<Driver::PulseCounterDriverStub::CounterSizeType, Driver::PulseCounterDriverStub::PULSE_COUNTER_AMOUNT> pulseCounters = {0};

// Expose the array pointer for C compatibility
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
    PulseCounterDriverStub::PulseCounterDriverStub()
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
        //    printf("PulseCounterDriverStub::getMeasurement()\n");
        return pulseCounters[0];
    }

    void PulseCounterDriverStub::clearMeasurement()
    {
    }

}
