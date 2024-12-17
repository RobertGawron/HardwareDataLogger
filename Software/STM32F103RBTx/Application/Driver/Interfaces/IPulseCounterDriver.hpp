/**
 * @file IPulseCounterDriver.hpp
 * @brief Defines the IPulseCounterDriver interface for interacting with pulse counter hardware.
 */

#ifndef IPulseCounterDriver_h
#define IPulseCounterDriver_h

#include "Driver/Inc/DriverState.hpp"
#include "Driver/Inc/PulseCounterIdentifier.hpp"

namespace Driver
{
    /**
     * @class IPulseCounterDriver
     * @brief Interface for pulse counter drivers.
     *
     * This interface provides the base functionality for pulse counter drivers, which are used to
     * interact with hardware that counts pulses, such as for frequency or event counting applications.
     * Derived classes are expected to implement the specific functionality required for their respective hardware.
     */
    class IPulseCounterDriver : public DriverState
    {
    public:
        using CounterSizeType = std::uint32_t; // Define a type alias for the max value of the counter (in bits)

        explicit IPulseCounterDriver() = default;

        /**
         * @brief Virtual destructor for IPulseCounterDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IPulseCounterDriver() override = default;

        virtual CounterSizeType getMeasurement() = 0;
        virtual void clearMeasurement() = 0;
    };
}

#endif // IPulseCounterDriver_h
