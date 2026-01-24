module;

#include <concepts>
#include <cstdint>

export module BusinessLogic.TickableConcept;

export namespace BusinessLogic
{
    /**
     * @brief Concept for a cooperative scheduled task.
     *
     * A scheduled task must provide:
     * - bool tick() noexcept;
     *
     * The noexcept requirement is important because the system is built without exceptions
     * and tasks are executed from a scheduler where failures must be reported via return
     * values rather than exceptions.
     */
    template <typename T>
    concept TickableConcept =
        requires(T &t) {
            { t.tick() } noexcept -> std::same_as<bool>;
        };
}