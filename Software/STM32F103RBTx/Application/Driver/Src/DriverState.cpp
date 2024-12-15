#include "Driver/Inc/DriverState.hpp"

namespace Driver
{
    bool DriverState::initialize()
    {
        if (onInitialize())
        {
            setState(State::Initialized);
            return true;
        }
        return false;
    }

    bool DriverState::start()
    {
        if (getState() == State::Initialized && onStart())
        {
            setState(State::Start);
            setState(State::Running);
            return true;
        }
        return false;
    }

    bool DriverState::stop()
    {
        if (getState() == State::Running && onStop())
        {
            setState(State::Stop);
            return true;
        }
        return false;
    }

    bool DriverState::reset()
    {
        if (onReset())
        {
            setState(State::Reset);
            return true;
        }
        return false;
    }

    DriverState::State DriverState::getState() const
    {
        return currentState;
    }

    bool DriverState::isInState(DriverState::State state) const
    {
        return currentState == state;
    }

    void DriverState::setState(DriverState::State newState)
    {
        currentState = newState;
    }
}
