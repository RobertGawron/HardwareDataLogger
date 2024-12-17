/**
 * @file IPulseCounterDriver.hpp
 * @brief Defines the IPulseCounterDriver interface for interacting with pulse counter hardware.
 */

#ifndef IPulseCounterDriver_h
#define IPulseCounterDriver_h

#include "Driver/Inc/DriverState.hpp"

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
        /**
         * @brief Default constructor for IPulseCounterDriver.
         */
        explicit IPulseCounterDriver() = default;

        /**
         * @brief Virtual destructor for IPulseCounterDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IPulseCounterDriver() override = default;
    };
}

#endif // IPulseCounterDriver_h
