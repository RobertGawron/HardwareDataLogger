#include "PulseCounterDriverStub.hpp"

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
}
