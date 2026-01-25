module;

#include <cstdint>
#include <concepts>
#include <type_traits>

export module Driver.DriverComponent;

export namespace Driver
{
    /**
     * @brief Detects presence of any member callable as t.onInit().
     *
     * @details
     * This concept is intentionally weak: it matches any onInit with any return type and
     * any exception specification. It is used for defensive enforcement to reject
     * incorrectly-typed hooks.
     */
    template <typename T>
    concept HasAnyOnInit = requires(T &t) { t.onInit(); };

    /**
     * @brief Detects a compliant initialization hook.
     *
     * @details
     * A compliant hook must have the exact semantic contract required by the framework:
     * - signature: bool onInit() noexcept;
     * - returns true on success, false on failure.
     */
    template <typename T>
    concept HasValidOnInit =
        requires(T &t) {
            { t.onInit() } noexcept -> std::same_as<bool>;
        };

    /**
     * @brief Detects presence of any member callable as t.onStart().
     *
     * @details
     * Used for defensive enforcement to reject incorrectly-typed hooks.
     */
    template <typename T>
    concept HasAnyOnStart = requires(T &t) { t.onStart(); };

    /**
     * @brief Detects a compliant start hook.
     *
     * @details
     * Required contract:
     * - signature: bool onStart() noexcept;
     * - returns true on success, false on failure.
     */
    template <typename T>
    concept HasValidOnStart =
        requires(T &t) {
            { t.onStart() } noexcept -> std::same_as<bool>;
        };

    /**
     * @brief Detects presence of any member callable as t.onStop().
     *
     * @details
     * Used for defensive enforcement to reject incorrectly-typed hooks.
     */
    template <typename T>
    concept HasAnyOnStop = requires(T &t) { t.onStop(); };

    /**
     * @brief Detects a compliant stop hook.
     *
     * @details
     * Required contract:
     * - signature: bool onStop() noexcept;
     * - returns true on success, false on failure.
     */
    template <typename T>
    concept HasValidOnStop =
        requires(T &t) {
            { t.onStop() } noexcept -> std::same_as<bool>;
        };

    /**
     * @brief Lifecycle helper base class using C++23 deducing-this (no vtable).
     *
     * @details
     * This class implements a small deterministic lifecycle state machine intended for
     * embedded drivers and components. It provides a non-virtual interface:
     * - init()
     * - start()
     * - stop()
     * - tick()
     *
     * Hooks are statically dispatched to derived types (no RTTI, no exceptions, no allocation).
     *
     * Hook policy (defensive):
     * - If a derived type provides a hook with the correct signature, it will be called.
     * - If a derived type provides a hook with an incorrect signature, compilation fails
     *   (see static_assert messages in init/start/stop).
     * - If a derived type does not provide a hook, it is treated as a successful no-op,
     *   except tick(): if onTick() is not provided, tick() returns false.
     *
     * State machine:
     * - Transitions are validated by isTransitionAllowed().
     * - The class stores only the current state.
     *
     * @note This class does not implement rollback on hook failure. If init/start/stop hook
     *       returns false, the state remains at the target state that was entered before invoking
     *       the hook.
     */
    class DriverComponent
    {
    public:
        /// @brief Constructs a component in RESET state.
        constexpr DriverComponent() noexcept {};

        /// @brief Non-copyable to prevent slicing and duplicated lifecycle state.
        DriverComponent(const DriverComponent &) = delete;

        /// @brief Non-copyable to prevent slicing and duplicated lifecycle state.
        DriverComponent &operator=(const DriverComponent &) = delete;

        /// @brief Non-movable to keep ownership/lifetime rules explicit.
        DriverComponent(DriverComponent &&) = delete;

        /// @brief Non-movable to keep ownership/lifetime rules explicit.
        DriverComponent &operator=(DriverComponent &&) = delete;

        /**
         * @brief Lifecycle state.
         *
         * @details
         * Values are explicit to keep diagnostics stable and compact (uint8_t).
         */
        enum class State : std::uint8_t
        {
            /// @brief Constructed / reset state.
            RESET = 0xFF,

            /// @brief Successfully initialized.
            INITIALIZED = 0x01,

            /// @brief Start sequence is in progress.
            STARTING = 0x02,

            /// @brief Component is running and tick() may execute work.
            RUNNING = 0x03,

            /// @brief Component is stopped.
            STOPPED = 0x04
        };

        /**
         * @brief Transitions RESET -> INITIALIZED and optionally calls Self::onInit().
         *
         * @tparam Self Deduced dynamic type (derived component type).
         * @param self  Deduced object instance.
         *
         * @details
         * - Validates hook signature policy for onInit().
         * - Performs the state transition (if allowed).
         * - If Self defines `bool onInit() noexcept`, it is invoked.
         *
         * @return True if transition succeeded and (if present) onInit returned true.
         */
        template <typename Self>
        [[nodiscard]] bool init(this Self &self) noexcept
        {
            static_assert(!HasAnyOnInit<Self> || HasValidOnInit<Self>,
                          "Invalid onInit() detected. Policy: either provide 'bool onInit() noexcept' "
                          "or do not provide onInit() at all.");

            bool status = self.setState(State::INITIALIZED);

            if (status)
            {
                if constexpr (requires(Self &s) { { s.onInit() } noexcept -> std::same_as<bool>; })
                {
                    status = self.onInit();
                }
            }

            return status;
        }

        /**
         * @brief Transitions INITIALIZED -> STARTING -> RUNNING and optionally calls Self::onStart().
         *
         * @tparam Self Deduced dynamic type (derived component type).
         * @param self  Deduced object instance.
         *
         * @details
         * - Validates hook signature policy for onStart().
         * - Performs transition to STARTING (if allowed).
         * - If Self defines `bool onStart() noexcept`, it is invoked.
         * - If successful, transitions to RUNNING (if allowed).
         *
         * @return True if all required transitions succeeded and (if present) onStart returned true.
         */
        template <typename Self>
        [[nodiscard]] bool start(this Self &self) noexcept
        {
            static_assert(!HasAnyOnStart<Self> || HasValidOnStart<Self>,
                          "Invalid onStart() detected. Policy: either provide 'bool onStart() noexcept' "
                          "or do not provide onStart() at all.");

            bool status = self.setState(State::STARTING);

            if (status)
            {
                if constexpr (requires(Self &s) { { s.onStart() } noexcept -> std::same_as<bool>; })
                {
                    status = self.onStart();
                }
            }

            if (status)
            {
                status = self.setState(State::RUNNING);
            }

            return status;
        }

        /**
         * @brief Transitions RUNNING/STARTING -> STOPPED and optionally calls Self::onStop().
         *
         * @tparam Self Deduced dynamic type (derived component type).
         * @param self  Deduced object instance.
         *
         * @details
         * - Validates hook signature policy for onStop().
         * - Performs transition to STOPPED (if allowed).
         * - If Self defines `bool onStop() noexcept`, it is invoked.
         *
         * @return True if transition succeeded and (if present) onStop returned true.
         */
        template <typename Self>
        [[nodiscard]] bool stop(this Self &self) noexcept
        {
            static_assert(!HasAnyOnStop<Self> || HasValidOnStop<Self>,
                          "Invalid onStop() detected. Policy: either provide 'bool onStop() noexcept' "
                          "or do not provide onStop() at all.");

            bool status = self.setState(State::STOPPED);

            if (status)
            {
                if constexpr (requires(Self &s) { { s.onStop() } noexcept -> std::same_as<bool>; })
                {
                    status = self.onStop();
                }
            }

            return status;
        }

        /**
         * @brief Executes one cooperative tick when RUNNING.
         *
         * @tparam Self Deduced dynamic type (derived component type).
         * @param self  Deduced object instance.
         *
         * @details
         * tick() executes work only when the component is in RUNNING state.
         * If Self provides `bool onTick() noexcept`, it is invoked; otherwise tick() returns false.
         *
         * @return True if onTick() exists and returned true; false otherwise.
         */
        template <typename Self>
        [[nodiscard]] bool tick(this Self &self) noexcept
        {
            bool status = false;

            if (self.getState() == State::RUNNING) [[likely]]
            {
                if constexpr (requires(Self &s) { { s.onTick() } noexcept -> std::same_as<bool>; })
                {
                    status = self.onTick();
                }
            }

            return status;
        }

        /**
         * @brief Returns the current lifecycle state.
         * @return Current state value.
         */
        [[nodiscard]] constexpr State getState() const noexcept
        {
            return state;
        }

    private:
        /// @brief Initial state at construction.
        static constexpr State DEFAULT_INITIAL_STATE = State::RESET;

        /// @brief Current lifecycle state (single-byte storage).
        State state{DEFAULT_INITIAL_STATE};

        /**
         * @brief Validates and applies a state transition.
         *
         * @param newState Requested target state.
         * @return True if the transition is allowed and the state was updated; false otherwise.
         */
        [[nodiscard]] constexpr bool setState(State newState) noexcept
        {
            bool status = false;

            if (isTransitionAllowed(state, newState)) [[likely]]
            {
                state = newState;
                status = true;
            }

            return status;
        }

        /**
         * @brief Checks whether a transition between two states is allowed.
         *
         * @param current Current state.
         * @param next    Requested next state.
         * @return True if allowed, false otherwise.
         */
        [[nodiscard]] static constexpr bool isTransitionAllowed(State current, State next) noexcept
        {
            return ((current == State::RESET) && (next == State::INITIALIZED)) ||
                   ((current == State::INITIALIZED) && (next == State::STARTING)) ||
                   ((current == State::STARTING) && ((next == State::RUNNING) || (next == State::STOPPED))) ||
                   ((current == State::RUNNING) && ((next == State::RUNNING) || (next == State::STOPPED))) ||
                   ((current == State::STOPPED) && ((next == State::STARTING) || (next == State::RESET)));
        }
    };

    /**
     * @brief Ensures deterministic layout and ABI characteristics of DriverComponent.
     *
     * @details
     * These assertions are part of defensive programming and are intended to detect accidental
     * changes that would add hidden state, ownership, or non-deterministic layout.
     */
    static_assert(std::is_standard_layout_v<DriverComponent>,
                  "DriverComponent must have standard layout for predictable representation.");
    static_assert(std::is_trivially_destructible_v<DriverComponent>,
                  "DriverComponent must be trivially destructible (no owned resources).");

    /// @brief Ensures State remains an enum (for stable storage and diagnostics).
    static_assert(std::is_enum_v<DriverComponent::State>,
                  "DriverComponent::State must remain an enum type.");

    /// @brief Ensures the enum underlying type remains uint8_t (size/ABI stability).
    static_assert(std::is_same_v<std::underlying_type_t<DriverComponent::State>, std::uint8_t>,
                  "DriverComponent::State underlying type must be std::uint8_t for deterministic storage.");

    /// @brief Ensures the stored state is exactly one byte.
    static_assert(sizeof(DriverComponent::State) == sizeof(std::uint8_t),
                  "DriverComponent::State must be exactly 1 byte.");

    /// @brief Ensures the component stays minimal (state only) for size-critical embedded builds.
    static_assert(sizeof(DriverComponent) == sizeof(DriverComponent::State),
                  "DriverComponent is expected to store only the state (no hidden members).");
} // namespace Driver