module;

#include <cstdint>

export module Driver.CoreClockConfig;

export namespace Driver
{
    /**
     * @brief Core clock configuration used for cycle-based timing.
     *
     * @details
     * This constant is used to convert time budgets (us/ms) to CPU cycles for
     * high-resolution timing based on the CPU cycle counter.
     *
     * Keep this value consistent with the actual configured system clock.
     */
    inline constexpr std::uint32_t coreHz = 72'000'000U; // todo could it be taken from HAL?

    static_assert(coreHz > 0U, "coreHz must be greater than 0.");
    static_assert((coreHz % 1'000U) == 0U, "coreHz should be divisible by 1000 for ms conversions.");
}