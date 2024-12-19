/**
 * @file PulseCounterDriver.hpp
 * @brief Defines the PulseCounterDriver class for interacting with pulse counter hardware.
 */

#ifndef PulseCounterDriver_h
#define PulseCounterDriver_h

#include "Driver/Interfaces/IPulseCounterDriver.hpp"

extern "C"
{
    void incrementPulseCounter(std::uint8_t counterId);
}

namespace Driver
{
    /**
     * @class PulseCounterDriver
     * @brief Implements the pulse counter driver interface for managing pulse counting operations.
     *
     * The PulseCounterDriver class provides methods to initialize, start, stop, and reset the pulse counter hardware.
     * It inherits from the IPulseCounterDriver interface and implements the required driver state transitions.
     */
    class PulseCounterDriver : public IPulseCounterDriver
    {
    public:
        static const std::uint8_t PULSE_COUNTER_AMOUNT = 4u;

        explicit PulseCounterDriver(PulseCounterIdentifier deviceIdentifier);

        PulseCounterDriver() = delete;
        /**
         * @brief Default destructor for PulseCounterDriver.
         *
         * Ensures proper cleanup of the driver.
         */
        ~PulseCounterDriver() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        PulseCounterDriver(const PulseCounterDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return PulseCounterDriver& The assigned object.
         */
        PulseCounterDriver &operator=(const PulseCounterDriver &) = delete;

        IPulseCounterDriver::CounterSizeType getMeasurement() override;
        void clearMeasurement() override;

        /**
         * @brief Initializes the pulse counter driver.
         *
         * Prepares the pulse counter hardware for use.
         * @return True if initialization was successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the pulse counter driver.
         *
         * Begins counting pulses using the pulse counter hardware.
         * @return True if the driver started successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the pulse counter driver.
         *
         * Halts pulse counting operations.
         * @return True if the driver stopped successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the pulse counter driver.
         *
         * Resets the pulse counter hardware, clearing any internal state or counters.
         * @return True if the driver reset successfully, false otherwise.
         */
        bool onReset() override;

    private:
        CounterSizeType &value;
    };
}

#endif // PulseCounterDriver_h
