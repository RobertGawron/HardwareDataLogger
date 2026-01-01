/**
 * @file PulseCounterDriver.hpp
 * @brief Defines the PulseCounterDriver class for interacting with pulse counter hardware.
 */

#ifndef PulseCounterDriver_h
#define PulseCounterDriver_h

#include "Driver/Interface/IPulseCounterDriver.hpp"

extern "C"
{
    /**
     * @brief Increments the pulse counter in interrupt handler.
     *
     * This function is called by the hardware interrupt handler when a pulse is detected.
     * @param counterId Identifier of the pulse counter to increment.
     */
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
        /** @brief Number of available pulse counters. */
        static const std::uint8_t PULSE_COUNTER_AMOUNT = 4U;

        /**
         * @brief Constructs a PulseCounterDriver with a specific device identifier.
         * @param deviceIdentifier Identifier of the pulse counter device.
         */
        explicit PulseCounterDriver(PulseCounterId deviceIdentifier);

        PulseCounterDriver() = delete; ///< Deleted default constructor prevents instantiation without identifier.

        /**
         * @brief Default destructor for PulseCounterDriver.
         *
         * Ensures proper cleanup of the driver.
         */
        ~PulseCounterDriver() override = default;

        PulseCounterDriver(const PulseCounterDriver &) = delete;            ///< Deleted copy constructor prevents copying.
        PulseCounterDriver &operator=(const PulseCounterDriver &) = delete; ///< Deleted assignment operator prevents assignment.

        /**
         * @brief Retrieves the current pulse count value.
         * @return The current pulse count measurement.
         */
        IPulseCounterDriver::CounterSizeType getMeasurement() override;

        /**
         * @brief Resets the pulse counter to zero.
         */
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
        /** @brief Reference to the current pulse counter value. */
        CounterSizeType &value;
    };
}

#endif // PulseCounterDriver_h
