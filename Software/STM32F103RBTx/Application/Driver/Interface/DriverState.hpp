#ifndef DriverState_h
#define DriverState_h

#include <cstdint>

namespace Driver
{
    /**
     * @class DriverState
     * @brief Manages the state of a driver with lifecycle management.
     *
     * The DriverState class provides a template for managing the state of a driver, including initialization,
     * starting, stopping, and resetting. It uses a state machine pattern to transition between different driver states.
     */
    class DriverState
    {
    public:
        /**
         * @brief Enumeration representing the various states a driver can be in.
         */
        enum class State : std::uint8_t
        {
            Reset = 0xff,      /**< Driver is in the reset state, the initial state after construction. */
            Initialized = 0x1, /**< Driver has been initialized but not started. */
            Start = 0x2,       /**< Driver is in the process of starting. */
            Running = 0x3,     /**< Driver is currently running. */
            Stop = 0x4         /**< Driver has been stopped. */
        };

        /**
         * @brief Default constructor.
         *
         * Initializes the driver state to Reset.
         */
        DriverState() = default;

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~DriverState() = default;

        /**
         * @brief Initializes the driver.
         *
         * Calls the `onInitialize` method, which must be implemented by derived classes to perform
         * driver-specific initialization tasks. Transitions the state to Initialized upon success.
         *
         * @return true if initialization is successful, false otherwise.
         */
        virtual bool initialize();

        /**
         * @brief Starts the driver.
         *
         * Calls the `onStart` method, which must be implemented by derived classes to perform
         * driver-specific start tasks. Transitions the state to Start and then to Running upon success.
         *
         * @return true if starting is successful, false otherwise.
         */
        virtual bool start();
        /**
         * @brief Stops the driver.
         *
         * Calls the `onStop` method, which must be implemented by derived classes to perform
         * driver-specific stop tasks. Transitions the state to Stop upon success.
         *
         * @return true if stopping is successful, false otherwise.
         */
        virtual bool stop();

        /**
         * @brief Resets the driver.
         *
         * Calls the `onReset` method, which must be implemented by derived classes to perform
         * driver-specific reset tasks. Transitions the state to Reset upon success.
         *
         * @return true if resetting is successful, false otherwise.
         */
        virtual bool reset();
        /**
         * @brief Gets the current state of the driver.
         *
         * Returns the current state of the driver.
         *
         * @return The current state of the driver.
         */
        [[nodiscard]] virtual State getState() const;

        /**
         * @brief Checks if the driver is in a specific state.
         *
         * Compares the current state of the driver to the provided state.
         *
         * @param state The state to check against.
         * @return true if the driver is in the specified state, false otherwise.
         */
        [[nodiscard]] virtual bool isInState(State state) const;

    protected:
        /**
         * @brief Sets the state of the driver.
         *
         * Allows derived classes to change the state of the driver.
         *
         * @param newState The new state to transition to.
         */
        virtual void setState(State newState);

        /**
         * @brief Abstract method to handle driver-specific initialization.
         *
         * Derived classes must implement this method to perform specific initialization tasks.
         * This method is called within the `initialize()` method as part of the Template Method pattern.
         *
         * @return true if initialization is successful, false otherwise.
         */
        virtual bool onInitialize() = 0;

        /**
         * @brief Abstract method to handle driver-specific start tasks.
         *
         * Derived classes must implement this method to perform specific start tasks.
         * This method is called within the `start()` method as part of the Template Method pattern.
         *
         * @return true if the start is successful, false otherwise.
         */
        virtual bool onStart() = 0;

        /**
         * @brief Abstract method to handle driver-specific stop tasks.
         *
         * Derived classes must implement this method to perform specific stop tasks.
         * This method is called within the `stop()` method as part of the Template Method pattern.
         *
         * @return true if the stop is successful, false otherwise.
         */
        virtual bool onStop() = 0;

        /**
         * @brief Abstract method to handle driver-specific reset tasks.
         *
         * Derived classes must implement this method to perform specific reset tasks.
         * This method is called within the `reset()` method as part of the Template Method pattern.
         *
         * @return true if the reset is successful, false otherwise.
         */
        virtual bool onReset() = 0;

    private:
        State currentState = State::Reset; /**< Holds the current state of the driver. */
    };
}

#endif // DriverState_h
