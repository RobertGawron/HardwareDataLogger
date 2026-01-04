#pragma once

#include <cstdint>
#include <concepts>

namespace Device
{
    enum class State : std::uint8_t
    {
        RESET = 0xFF,
        INITIALIZED = 0x01,
        STARTING = 0x02,
        RUNNING = 0x03,
        STOPPED = 0x04
    };

    /**
     * @brief Refined concept for the new Deduced-this pattern
     */
    template <typename T>
    concept DeviceLifecycle = requires(T t) {
        { t.onInit() } noexcept -> std::same_as<bool>;
        { t.onStart() } noexcept -> std::same_as<bool>;
        { t.onStop() } noexcept -> std::same_as<bool>;
        //   { t.onTick() } noexcept -> std::same_as<bool>;
    };

    /**
     * @class DeviceComponent
     * @brief Non-template base class using C++23 Deducing This.
     * Guaranteed zero vtable overhead and optimized for short binary output.
     */
    class DeviceComponent
    {
    public:
        static constexpr State DEFAULT_INITIAL_STATE = State::RESET;

        constexpr DeviceComponent() noexcept = default;

        // Deleted copy/move to prevent state slicing
        DeviceComponent(const DeviceComponent &) = delete;
        DeviceComponent &operator=(const DeviceComponent &) = delete;

        // --- Public Interface (Static Dispatch via Deducing This) ---

        template <typename Self>
        [[nodiscard]] bool init(this Self &self) noexcept
        {
            return self.exec(State::INITIALIZED, &Self::onInit);
        }

        template <typename Self>
        [[nodiscard]] bool start(this Self &self) noexcept
        {
            if (!self.exec(State::STARTING, &Self::onStart))
            {
                return false;
            }
            return self.setState(State::RUNNING);
        }

        template <typename Self>
        [[nodiscard]] bool stop(this Self &self) noexcept
        {
            return self.exec(State::STOPPED, &Self::onStop);
        }

        template <typename Self>
        [[nodiscard]] bool tick(this Self &self) noexcept
        {
            // Hot path optimization: Use [[unlikely]] for non-running states
            if (self.currentState != State::RUNNING) [[unlikely]]
            {
                return false;
            }
            return self.onTick();
        }

        [[nodiscard]] constexpr State getState() const noexcept { return currentState; }

    protected:
        // Transition helper now uses the deduced self
        template <typename Self, typename Func>
        [[nodiscard]] bool exec(this Self &self, State target, Func func) noexcept
        {
            if (!self.setState(target)) [[unlikely]]
            {
                return false;
            }
            return (self.*func)();
        }

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
