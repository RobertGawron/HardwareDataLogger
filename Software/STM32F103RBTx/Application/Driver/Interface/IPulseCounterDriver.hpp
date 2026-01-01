/**
 * @file IPulseCounterDriver.hpp
 * @brief Defines the IPulseCounterDriver interface for interacting with pulse counter hardware.
 */

#ifndef IPulseCounterDriver_h
#define IPulseCounterDriver_h

#include "Driver/Interface/DriverState.hpp"
#include "Driver/Interface/PulseCounterId.hpp"

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
         * @brief Type representing the counter value size.
         *
         * Defines the integer type used for storing pulse count values.
         */
        using CounterSizeType = std::uint32_t;

        /**
         * @brief Default constructor for IPulseCounterDriver.
         */
        explicit IPulseCounterDriver() = default;

        IPulseCounterDriver(const IPulseCounterDriver &) = delete;
        IPulseCounterDriver &operator=(const IPulseCounterDriver &) = delete;
        IPulseCounterDriver(IPulseCounterDriver &&) = delete;
        IPulseCounterDriver &operator=(IPulseCounterDriver &&) = delete;

        /**
         * @brief Virtual destructor for IPulseCounterDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IPulseCounterDriver() override = default;

        /**
         * @brief Retrieves the current pulse count value.
         *
         * @return The current pulse count value.
         */
        virtual CounterSizeType getMeasurement() = 0;

        /**
         * @brief Resets the pulse counter to zero.
         */
        virtual void clearMeasurement() = 0;
    };
}

#endif // IPulseCounterDriver_h
