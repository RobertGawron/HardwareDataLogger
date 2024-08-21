
#ifndef PulseCounterDriverStub_h
#define PulseCounterDriverStub_h

#include "IPulseCounterDriver.hpp"

namespace Driver
{
    class PulseCounterDriverStub : public IPulseCounterDriver
    {
    public:
        explicit PulseCounterDriverStub();

        virtual ~PulseCounterDriverStub() = default;

        // Delete copy constructor and assignment operator
        PulseCounterDriverStub(const PulseCounterDriverStub &) = delete;
        PulseCounterDriverStub &operator=(const PulseCounterDriverStub &) = delete;

        bool onInitialize() override;

        bool onStart() override;

        bool onStop() override;

        bool onReset() override;
    };
}

#endif
