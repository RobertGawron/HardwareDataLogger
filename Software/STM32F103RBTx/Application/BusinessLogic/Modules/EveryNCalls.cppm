module;
#include <cstdint>
export module BusinessLogic.EveryNCalls;

import BusinessLogic.TickableConcept;

export namespace BusinessLogic
{
    template <std::uint32_t N, TickableConcept T>
    class EveryNCalls final
    {
    public:
        static_assert(N > 0U);

        explicit constexpr EveryNCalls(T &innerTask) noexcept
            : inner(innerTask)
        {
        }

        [[nodiscard]] auto tick() noexcept -> bool
        {
            // Called each time the scheduler invokes this TaskId
            ++counter;
            if (counter < N)
            {
                return true; // "not time yet", but not an error
            }

            counter = 0U;
            return inner.tick(); // call the real task only every Nth time
        }

    private:
        T &inner;
        std::uint32_t counter{0U};
    };
}