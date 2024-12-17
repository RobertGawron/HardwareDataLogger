
#ifndef PulseCounterDriverStub_h
#define PulseCounterDriverStub_h

#include "Driver/Interfaces/IPulseCounterDriver.hpp"

extern "C"
{
    void incrementPulseCounter(std::uint8_t counterId);
}

namespace Driver
{
    class PulseCounterDriverStub : public IPulseCounterDriver
    {
    public:
        static const std::uint8_t PULSE_COUNTER_AMOUNT = 4u;

        explicit PulseCounterDriverStub(PulseCounterIdentifier id);

        explicit PulseCounterDriverStub();

        virtual ~PulseCounterDriverStub() = default;

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
