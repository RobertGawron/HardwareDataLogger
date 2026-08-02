module;
#include <cstdint>
export module BusinessLogic.EveryNCalls;

import BusinessLogic.TickableConcept;

export namespace BusinessLogic
{
    template <TickableConcept T, std::uint32_t N>
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

            const bool shouldRun = (counter >= N);
            bool result = true;

            if (shouldRun)
            {
                counter = 0U;
                result = inner.tick(); // call the real task only every Nth time
            }

            return result;
        }

    private:
        T &inner;
        std::uint32_t counter{0U};
    };
}