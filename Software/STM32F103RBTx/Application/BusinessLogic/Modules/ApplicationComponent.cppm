module;

#include <cstdint>
#include <concepts>

export module BusinessLogic.ApplicationComponent;

export namespace BusinessLogic
{
    /**
     * @brief Component lifecycle states enforcing initialization order.
     * Flow: RESET -> INITIALIZED -> STARTING -> RUNNING <-> STOPPED -> RESET
     */
    enum class State : std::uint8_t
    {
        RESET = 0xFF,
        INITIALIZED = 0x01,
        STARTING = 0x02,
        RUNNING = 0x03,
        STOPPED = 0x04
    };

    /**
     * @brief Requires lifecycle methods for managed component execution.
     * Components must implement onInit(), onStart(), onStop(), onTick() returning bool.
     */
    template <typename T>
    concept ApplicationLifecycle = requires(T t) {
        { t.onInit() } noexcept -> std::same_as<bool>;
        { t.onStart() } noexcept -> std::same_as<bool>;
        { t.onStop() } noexcept -> std::same_as<bool>;
        { t.onTick() } noexcept -> std::same_as<bool>;
    };

    /**
     * @class ApplicationComponent
     * @brief Base class managing component lifecycle through validated state transitions.
     * Prevents invalid state sequences (e.g., running before initialization).
     * Derived classes override onInit/onStart/onStop/onTick to define behavior.
     * Not thread-safe: caller must serialize state transitions.
     */
    class ApplicationComponent
    {
    public:
        static constexpr State DEFAULT_INITIAL_STATE = State::RESET;

        constexpr ApplicationComponent() noexcept = default;

        ApplicationComponent(const ApplicationComponent &) = delete;
        ApplicationComponent &operator=(const ApplicationComponent &) = delete;

        /**
         * @brief Performs component initialization from RESET state.
         * @return true if transition to INITIALIZED succeeded and onInit() completed successfully.
         */
        template <typename Self>
        [[nodiscard]] bool init(this Self &self) noexcept
        {
            return self.exec(State::INITIALIZED, &Self::onInit);
        }

        /**
         * @brief Starts component execution, transitioning to operational state.
         * @return true if STARTING transition, onStart() callback, and RUNNING transition all succeed.
         */
        template <typename Self>
        [[nodiscard]] bool start(this Self &self) noexcept
        {
            if (!self.exec(State::STARTING, &Self::onStart))
            {
                return false;
            }
            return self.setState(State::RUNNING);
        }

        /**
         * @brief Halts component execution, allowing restart or reset.
         * @return true if transition to STOPPED succeeded and onStop() completed successfully.
         */
        template <typename Self>
        [[nodiscard]] bool stop(this Self &self) noexcept
        {
            return self.exec(State::STOPPED, &Self::onStop);
        }

        /**
         * @brief Executes one iteration of component logic in RUNNING state.
         * @return true if component is RUNNING and onTick() succeeded, false otherwise.
         * @note Call repeatedly in main loop for continuous operation.
         */
        template <typename Self>
        [[nodiscard]] bool tick(this Self &self) noexcept
        {
            if (self.currentState != State::RUNNING) [[unlikely]]
            {
                return false;
            }
            return self.onTick();
        }

        /**
         * @brief Reads current component state.
         * @return Current lifecycle state without modifying component.
         */
        [[nodiscard]] constexpr State getState() const noexcept { return currentState; }

    protected:
        /**
         * @brief Executes state transition followed by lifecycle callback.
         * @param target Target state to transition into.
         * @param func Lifecycle method to invoke after successful transition.
         * @return true if transition permitted and callback succeeded.
         */
        template <typename Self, typename Func>
        [[nodiscard]] bool exec(this Self &self, State target, Func func) noexcept
        {
            if (!self.setState(target)) [[unlikely]]
            {
                return false;
            }
            return (self.*func)();
        }

        /**
         * @brief Attempts state transition with validation against state machine rules.
         * @param newState Target state to transition into.
         * @return true if transition allowed from current state, false if invalid.
         */
        [[nodiscard]] constexpr bool setState(State newState) noexcept
        {
            if (isValidTransition(currentState, newState)) [[likely]]
            {
                currentState = newState;
                return true;
            }
            return false;
        }

    private:
        State currentState = DEFAULT_INITIAL_STATE;

        /**
         * @brief Validates state transition against lifecycle rules.
         * Enforces sequence: RESET->INITIALIZED->STARTING->RUNNING<->STOPPED->RESET
         * @param current Source state.
         * @param next Destination state.
         * @return true if transition is valid, false otherwise.
         */
        [[nodiscard]] static constexpr bool isValidTransition(State current, State next) noexcept
        {
            switch (current)
            {
            case State::RESET:
                return next == State::INITIALIZED;
            case State::INITIALIZED:
                return next == State::STARTING;
            case State::STARTING:
                return next == State::RUNNING || next == State::STOPPED;
            case State::RUNNING:
                return next == State::RUNNING || next == State::STOPPED;
            case State::STOPPED:
                return next == State::STARTING || next == State::RESET;
            default:
                return false;
            }
        }
    };
}