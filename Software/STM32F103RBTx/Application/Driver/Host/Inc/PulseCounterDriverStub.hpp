
#ifndef PulseCounterDriverStub_h
#define PulseCounterDriverStub_h

#include "Driver/Interface/IPulseCounterDriver.hpp"

extern "C"
{
    void incrementPulseCounter(std::uint8_t counterId);
    void setPulseCounter(std::uint8_t counterId, std::uint32_t value);
}

namespace Driver
{
    class PulseCounterDriverStub : public IPulseCounterDriver
    {
    public:
        static const std::uint8_t PULSE_COUNTER_AMOUNT = 4u;

        explicit PulseCounterDriverStub(PulseCounterId id);

        PulseCounterDriverStub() = delete;

        ~PulseCounterDriverStub() override = default;

        // Delete copy constructor and assignment operator
        PulseCounterDriverStub(const PulseCounterDriverStub &) = delete;
        PulseCounterDriverStub &operator=(const PulseCounterDriverStub &) = delete;

        IPulseCounterDriver::CounterSizeType getMeasurement() override;
        void clearMeasurement() override;

        bool onInitialize() override;

        bool onStart() override;

        bool onStop() override;

        bool onReset() override;
    };
}

#endif
