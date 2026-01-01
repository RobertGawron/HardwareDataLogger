module;

#include <cstdint>

export module Driver.CycleCpu;

export namespace Driver
{
    /**
     * @brief CPU cycle counter type used by the high-resolution cycle clock.
     *
     * @details
     * This type represents raw ticks of the CPU cycle counter (e.g., DWT->CYCCNT on Cortex-M3).
     * The counter is monotonic modulo 2^32 and will wrap around. Elapsed time measurements
     * should therefore be computed using unsigned subtraction:
     * @code
     * CycleCpu elapsed = end - start;
     * @endcode
     *
     * The unit is CPU cycles (not microseconds). Conversion to time units should be performed
     * using the configured core frequency (see CycleBudget).
     */
    using CycleCpu = std::uint32_t;

    static_assert(sizeof(CycleCpu) == sizeof(std::uint32_t),
                  "CycleCpu must remain a 32-bit unsigned integer type.");
}