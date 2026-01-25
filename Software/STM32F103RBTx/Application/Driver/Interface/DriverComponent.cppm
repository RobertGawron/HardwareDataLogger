module;

#include <cstdint>
#include <concepts>
#include <type_traits>

export module Driver.DriverComponent;

export namespace Driver
{
    template <typename T>
    concept HasAnyOnInit = requires(T &t) { t.onInit(); };

    template <typename T>
    concept HasValidOnInit = requires(T &t) {
        { t.onInit() } noexcept -> std::same_as<bool>;
    };

    template <typename T>
    concept HasAnyOnStart = requires(T &t) { t.onStart(); };

    template <typename T>
    concept HasValidOnStart = requires(T &t) {
        { t.onStart() } noexcept -> std::same_as<bool>;
    };

    template <typename T>
    concept HasAnyOnStop = requires(T &t) { t.onStop(); };

    template <typename T>
    concept HasValidOnStop = requires(T &t) {
        { t.onStop() } noexcept -> std::same_as<bool>;
    };

    /**
     * @brief Non-virtual lifecycle base using C++23 deducing-this.
     *
     * @details
     * Derived types may implement any subset of:
     * - bool onInit() noexcept;
     * - bool onStart() noexcept;
     * - bool onStop() noexcept;
     * - bool onTick() noexcept;
     *
     * Missing hooks are treated as successful no-ops, except tick(): if onTick() is missing,
     * tick() returns false.
     */
    class DriverComponent
    {
    public:
        constexpr DriverComponent() noexcept {};

        DriverComponent(const DriverComponent &) = delete;
        DriverComponent &operator=(const DriverComponent &) = delete;
        DriverComponent(DriverComponent &&) = delete;
        DriverComponent &operator=(DriverComponent &&) = delete;

        enum class State : std::uint8_t
        {
            RESET = 0xFF,
            INITIALIZED = 0x01,
            STARTING = 0x02,
            RUNNING = 0x03,
            STOPPED = 0x04
        };

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

        [[nodiscard]] constexpr State getState() const noexcept
        {
            return state;
        }

    private:
        static constexpr State DEFAULT_INITIAL_STATE = State::RESET;
        State state{DEFAULT_INITIAL_STATE};

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

        [[nodiscard]] static constexpr bool isTransitionAllowed(State current, State next) noexcept
        {
            return ((current == State::RESET) && (next == State::INITIALIZED)) ||
                   ((current == State::INITIALIZED) && (next == State::STARTING)) ||
                   ((current == State::STARTING) && ((next == State::RUNNING) || (next == State::STOPPED))) ||
                   ((current == State::RUNNING) && ((next == State::RUNNING) || (next == State::STOPPED))) ||
                   ((current == State::STOPPED) && ((next == State::STARTING) || (next == State::RESET)));
        }
    };

    static_assert(std::is_standard_layout_v<DriverComponent>,
                  "DriverComponent must have standard layout for predictable representation.");

    static_assert(std::is_trivially_destructible_v<DriverComponent>,
                  "DriverComponent must be trivially destructible (no owned resources).");

    // State representation expectations
    static_assert(std::is_enum_v<DriverComponent::State>,
                  "DriverComponent::State must remain an enum type.");

    static_assert(std::is_same_v<std::underlying_type_t<DriverComponent::State>, std::uint8_t>,
                  "DriverComponent::State underlying type must be std::uint8_t for deterministic storage.");

    // Size expectations
    static_assert(sizeof(DriverComponent::State) == sizeof(std::uint8_t),
                  "DriverComponent::State must be exactly 1 byte.");

    static_assert(sizeof(DriverComponent) == sizeof(DriverComponent::State),
                  "DriverComponent is expected to store only the state (no hidden members).");

} // namespace Driver